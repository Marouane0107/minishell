/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:51:07 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/10 20:12:38 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_fail(int i)
{
	if (i < 0)
	{
		write(1, "error\n", 6);
		exit(1);
	}
}

void	msg_error(char *sp)
{
	putstr_fd("error: command not found: ", 1, sp);
	exit(127);
}

char	**ft_path(char **ev)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	tmp = NULL;
	path = NULL;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
		{
			path = ft_split(ev[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (path);
}

void	multiple(t_data *data, char **av, int ac)
{
	data->n = 2;
	data->fdin = open(av[1], O_RDONLY);
	if (data->fdin < 0)
		perror("open");
	data->fdout = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->fdout < 0)
	{
		perror("open");
		exit(1);
	}
}

t_data	*pars_inp(char **av, int ac, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->path = ft_path(env);
	data->av = av;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac >= 6)
			heredoc(av, ac, data);
		else
		{
			putstr_fd("error: not enough argument", 1, "");
			exit(1);
		}
	}
	else
		multiple(data, av, ac);
	return (data);
}
