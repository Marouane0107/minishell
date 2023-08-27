/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:58:37 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/27 03:53:03 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data)
{
	int		i;
	char	*path;
	char	*path_cmd;
	char	*cmd_path;

	i = 0;
	path = getenv("PATH");
	data->path = ft_split(path, ':');
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

// bad file descriptor error

void	changing_files(t_data *data, int fd[2])
{
	printf("in = %d\n", data->in);
	printf("out = %d\n", data->out);
	if (data->in != 0)
	{
		if (data->in > 0)
		{
			if (dup2(data->in, 0) == -1)
				perror("dup2");
		}
		if (data->in == -2 || data->in > 0)
		{
			if (dup2(fd[1], 0) == -1)
				perror("dup2");
			close(fd[0]);
		}
		if (data->in > 0)
			close(data->in);
		data->in = 0;
	}
	if (data->out != 1)
	{
		if (data->out > 2)
		{
			if (dup2(data->out, 1) == -1)
				perror("dup2");
		}
		if (dup2(fd[0], 1) == -1)
			perror("dup2");
		close(fd[1]);
		if (data->out > 2)
			close(data->out);
	}
}

void	ft_fork(t_data *data, pid_t *id, int fd[2])
{
	*id = fork();
	if (*id == -1)
	{
		perror("fork");
		exit(1);
	}
	if (*id == 0)
	{
		changing_files(data, fd);
		exec_cmd(data);
	}
	else if (*id > 0)
	{
		close(fd[1]);
		close(fd[0]);
		waitpid(*id, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
}

void	ft_exec(t_data *data)
{
	pid_t	pid;
	t_data	*tmp;
	int		fd[2];

	tmp = data;
	if (data->cmd && data->next)
	{
		while (tmp)
		{
			pipe(fd);
			if(pipe(fd) == -1)
				perror("pipe");
			ft_fork(tmp, &pid, fd);
			tmp = tmp->next;
			if(tmp)
				tmp->in = -2;
		}
	}
	else
	{
		ft_fork(data, &pid, fd);
	}
}
