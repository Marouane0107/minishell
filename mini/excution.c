/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:58:37 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/02 19:08:22 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_check(t_data *data)
{
	if (!data)
		return ;
	else if (ft_strcmp(data->cmd[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->cmd[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->cmd[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->cmd[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->cmd[0], "unset") == 0)
	ft_unset(data);
			else if (ft_strcmp(data->cmd[0], "exit") == 0)
		ft_exit(0);
	else
		exec_cmd(data);
}

void	get_cmd(t_data *data)
{
	t_data	*tmp;

	tmp = data;
	while (tmp && tmp->next)
	{
		if(!tmp->cmd)
		{
			tmp->cmd = tmp->next->cmd;
		}
		else
			return ;
	}
}

void	exec_cmd(t_data *data)
{
	int		i;
	char	*path;
	char	**path_part;
	char	*path_cmd;
	char	*cmd_path;

	i = 0;
	if (!data->cmd)
		return ;
	path = ft_getenv("PATH");
	path_part = ft_split(path, ':');
	get_cmd(data);
	while (path_part[i])
	{
		cmd_path = ft_strjoin(path_part[i], "/");
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

void	milti_pipe(t_data *data, int fd[2])
{
	pid_t	pid;
	t_data	*tmp;

	tmp = data;
	while (tmp)
	{
		pipe(fd);
		if(pipe(fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
			child(tmp, fd);
		else
			parent(tmp, fd);
		tmp = tmp->next;
	}
	ft_close(tmp, fd);
	while (waitpid(pid, NULL, 0) != -1);
}

void	ft_exec(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	if (data->cmd && data->next)
		milti_pipe(data, fd);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
			cmd_check(data);
		else
			waitpid(pid, NULL, 0);
	}
}
