/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:58:37 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/26 02:32:31 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(t_data *data)
{
	t_env	*tmp;
	char	*path;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
		{
			path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	data->path = ft_split(path, ':');
}

void	exec_cmd(t_data *data)
{
	int		i;
	char	*path_cmd;
	char	*cmd_path;

	i = 0;
	get_path(data);
	while (data->path[i])
	{
		cmd_path = ft_strjoin(data->path[i], "/");
		path_cmd = ft_strjoin(cmd_path, data->cmd[0]);
		if (access(path_cmd, X_OK) == -1)
			free(path_cmd);
		else if (execve(path_cmd, data->cmd, NULL) == -1)
		{
			printf("minishell: %s: command not found\n", data->cmd[0]);
			exit(127);
		}
		i++;
	}
	printf("minishell: %s: command not found\n", data->cmd[0]);
	exit(127);
}

void	ft_exec(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_cmd(data);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
			
	}
	else
		printf("Error\n");
}