/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:40:02 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/07 16:25:46 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	shlvl(t_data *data, char *s)
// {
// 	if (ft_strcmp(s, "./minishell") == 0)
// 	{
// 		g_lobal.i++;
// 		data->cmd[0] = ft_strdup("export");
// 		data->cmd[1] = ft_strjoin("SHLVL=", ft_itoa(g_lobal.i));
// 		ft_export(data);
// 		data->cmd[0] = ft_strdup("./minishell");
// 		free(data->cmd[1]);
// 		printf("im here\n");
// 	}	
// }
void child_sigint(int sigin)
{
	(void)sigin;
	printf("gfd\n");
	g_lobal.ex = 130;
}
void	check_cmd_path(t_data *data)
{
	int	i;
	extern char **environ;
	i = 0;
	if (!data->cmd)
		return ;
	while (data->cmd[i])
	{
		if (data->cmd[i][0] == '/' || data->cmd[i][0] == '.')
		{
			// shlvl(data, data->cmd[i]);
			printf("cmd : %s\n", data->cmd[i]);
			if (access(data->cmd[i], X_OK) == -1)
			{
				printf("%s: command not found\n", data->cmd[i]);
				exit(127);
			}
			else if (execve(data->cmd[i], data->cmd, environ) == -1)
			{
				printf("lmlawi\n");
				printf("%s: command not found\n", data->cmd[i]);
				exit(127);
			}
		}
		i++;
	}
}


void    exution( t_data *data, char **path_part, int i)
{
	char	*cmd_path;
	char	*path_cmd;
    extern char **environ;
	if (!*data->cmd[0])
	{
		printf("'': command not found\n");
		exit(127);
	}
	signal(SIGINT, child_sigint);
    while (path_part && path_part[i])
	{
		cmd_path = ft_strjoin(path_part[i], "/");
		path_cmd = ft_strjoin(cmd_path, data->cmd[0]);
		if (access(path_cmd, X_OK) == -1)
		{
			if (path_cmd)
				free(path_cmd);
		}
		else if (execve(path_cmd, data->cmd, environ) == -1)
		{
			
			printf("%s: command not found\n", data->cmd[0]);
			exit(127);
		}
		i++;
	}
}

void	exec_cmd(t_data *data)
{
	int		i;
	char	*path;
	char	**path_part;

	i = 0;
	if (!data->cmd || !*data->cmd)
		return ;
	path = ft_getenv("PATH");
	if (data->cmd[i][0] == '/' || data->cmd[i][0] == '.')
		check_cmd_path(data);
	if (!path)
	{
		printf("minishell: %s: No such file or directory\n", data->cmd[0]);
		exit(127);
	}
	path_part = ft_split(path, ':');
	get_cmd(data);
    exution(data, path_part, i);
	printf("%s: command not found\n", ft_strdup(data->cmd[0]));
	exit(127);
}
