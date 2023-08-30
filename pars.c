/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:45:25 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/14 00:14:54 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*pars_inp(char **av, int ac, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->path = ft_path(env);
	data->av = av;
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
	return (data);
}

char	**ft_path(char **ev)
{
	unsigned long	i;
	char			**path;

	i = 0;
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

char	*ft_access(char *path, char *cmd)
{
	int		j;
	char	*tmp;

	tmp = ft_strjoin(path, cmd);
	j = access(tmp, X_OK);
	if (j == 0)
	{
		free(cmd);
		return (tmp);
	}
	else
	{
		free(cmd);
		free(tmp);
		return (0);
	}
}

void	firstdup(t_data *data)
{
	if (data->fdin < 0)
		exit(1);
	else if (dup2(data->fdin, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
}

char	*ft_cmd(t_data *data, char *cmd)
{
	int		i;
	char	**sp;
	char	*pathcmd;

	i = 0;
	if (data->n == 2)
		firstdup(data);
	if (ft_strchr(cmd, '/'))
		return (cmd);
	sp = ft_split(cmd, ' ');
	if (data->path)
	{
		while (data->path[i])
		{
			pathcmd = ft_access(data->path[i], ft_strjoin("/", sp[0]));
			if (pathcmd)
			{
				ffree(sp);
				return (pathcmd);
			}
			free(pathcmd);
			i++;
		}
	}
	return (check_fail(0, sp[0]), NULL);
}
