/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:32:22 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/14 00:22:55 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	check_fail(pid);
	pid = fork();
	check_fail(pid);
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

void	ft_wait(int i, int j)
{
	waitpid(i, &j, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(j))
		exit(WEXITSTATUS(j));
}

int	main(int ac, char **av, char **env)
{
	int		j;
	int		i;
	t_data	*data;

	i = 0;
	j = 0;
	if (ac >= 5)
	{
		data = pars_inp(av, ac, env);
		while (av[data->n] && data->n < ac - 1)
		{
			data->args = ft_split(av[data->n], ' ');
			if (data->n == ac - 2)
				i = ft_fork(env, av[data->n], data, 1);
			else
				ft_fork(env, av[data->n], data, 0);
			ffree(data->args);
			data->n++;
		}
		ft_wait(i, j);
	}
	else
		putstr_fd("invalid argument", 1, "");
	return (0);
}
