/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:58:37 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/17 03:46:34 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_check(t_data *data)
{
	if (!data || !data->cmd)
		return (-1);
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
		ft_exit(data);
	else
		return (1);
	return (0);
}

int	milti_pipe(t_data *data, int fd[2])
{
	pid_t	pid;
	t_data	*tmp;

	tmp = data;
	while (tmp)
	{
		pipe(fd);
		if (pipe(fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			child(tmp, fd);
		}
		else
			parent(fd);
		tmp = tmp->next;
	}
	ft_close_pipe(fd);
	ft_close_file(tmp);
	return (pid);
}

void	ft_wait_ex(int i)
{
	int	status;
	int	j;
	int	b;

	status = 0;
	waitpid(i, &status, 0);
	b = 0;
	while (wait(&j) != -1)
	{
		if (WIFSIGNALED(j))
		{
			write(1, "\n", 1);
			b = 1;
			break ;
		}
	}
	if (WIFEXITED(status))
		g_lobal.ex = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (!b)
			write(1, "\n", 1);
		g_lobal.ex = WTERMSIG(status) + 128;
	}
}

void	singl_cmd(t_data *data, pid_t pid)
{
	out_in_file(data);
	if (cmd_check(data) > 0)
	{
		g_lobal.ex = 0;
		g_lobal.i = 1;
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exec_cmd(data);
			exit(g_lobal.ex);
		}
	}
	ft_close_file(data);
}

void	ft_exec(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	pid = 0;
	g_lobal.i = 0;
	signal(SIGINT, SIG_IGN);
	if (data->cmd && data->next)
	{
		g_lobal.ex = 0;
		g_lobal.i = 1;
		pid = milti_pipe(data, fd);
	}
	else
	{
		if (data->in == -3 || data->out == -3)
			return ;
		singl_cmd(data, pid);
	}
	if (g_lobal.i == 1)
		ft_wait_ex(pid);
}
