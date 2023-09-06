/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:58:37 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/07 00:18:16 by otamrani         ###   ########.fr       */
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
void sigint(int i)
{
	(void)i;
	printf("gfdsgfsdhyrenjthtey\n");
	signal(SIGINT, SIG_DFL);
	g_lobal.ex = 130;
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
		{
			signal(SIGINT, sigint);
			child(tmp, fd);
		}
		else
			parent(fd);
		tmp = tmp->next;
	}
	ft_close_pipe(fd);
	ft_close_file(tmp);
	while (waitpid(pid, NULL, 0) > 0);
	wait(NULL);
}

void	ft_exec(t_data *data)
{
	pid_t	pid;
	int		fd[2];
	g_lobal.ex = 0;
	signal(SIGINT, sigint_handler);
	if (data->cmd && data->next)
		milti_pipe(data ,fd);
	else
	{
		
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			out_in_file(data);
			if(cmd_check(data) > 0)
				exec_cmd(data);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			ft_close_file(data);
		}
		
	}
}
