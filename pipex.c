/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:06:57 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/14 00:16:41 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_fail(int i, char *sp)
{
	if (i < 0)
	{
		write(1, "error\n", 6);
		exit(1);
	}
	else if (sp)
	{
		putstr_fd("error: command not found: ", 1, sp);
		exit(127);
	}
}

void	ft_close_dup(int fdin, int fdout)
{
	if (close(fdout) == -1)
	{
		perror("close");
		exit(1);
	}
	if (dup2(fdin, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (close(fdin) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	checkdup(int pfdin, int pfdout, int fdout, int check)
{
	int	i;

	i = 0;
	if (dup2(pfdout, 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (check)
		i = dup2(fdout, 1);
	if (i == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (close(pfdin) == -1)
	{
		perror("close");
		exit(1);
	}
	if (close(pfdout) == -1)
	{
		perror("close");
		exit(1);
	}
}

int	ft_fork(char **env, char *arg, t_data *data, int check)
{
	pid_t	pid;
	int		fd[2];
	char	*path;

	pid = pipe(fd);
	check_fail(pid, 0);
	pid = fork();
	check_fail(pid, 0);
	if (pid == 0)
	{
		path = ft_cmd(data, arg);
		checkdup(fd[0], fd[1], data->fdout, check);
		execve(path, data->args, env);
		perror("execve");
		exit(127);
	}
	else
		ft_close_dup(fd[0], fd[1]);
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		j;
	t_data	*data;

	if (ac == 5)
	{
		data = pars_inp(av, ac, env);
		data->args = ft_split(av[2], ' ');
		ft_fork(env, av[2], data, 0);
		data->n = 3;
		ffree(data->args);
		data->args = ft_split(av[3], ' ');
		i = ft_fork(env, av[3], data, 1);
		waitpid(i, &j, 0);
		while (wait(NULL) != -1)
			;
		if (WIFEXITED(j))
			exit(WEXITSTATUS(j));
	}
	else
		putstr_fd("invalid argument", 1, "");
	return (0);
}
