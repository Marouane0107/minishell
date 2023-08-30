/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:05:50 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/14 00:27:02 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	stock(char *av, int fdin)
{
	char	*line;
	char	*tmp;

	write(1, "here_doc: ", 10);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(line, av) == 0)
			break ;
		write(1, "here_doc: ", 10);
		putstr_fd(line, fdin, 0);
		tmp = line;
		line = get_next_line(0);
		free(tmp);
	}
	free(line);
}

void	heredoc(char **av, int ac, t_data *data)
{
	data->n = 3;
	data->fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	data->fdin = open("her", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fdin < 0 || data->fdout < 0)
	{
		if (data->fdout < 0)
			putstr_fd("No such file or directory: ", 1, av[ac - 1]);
		if (data->fdin < 0)
			perror("open");
		exit(1);
	}
	stock(av[2], data->fdin);
	data->fdin = open("her", O_RDONLY, 0644);
	if (data->fdin < 0)
	{
		perror("open");
		exit(1);
	}
	if (dup2(data->fdin, 0) == -1)
	{
		perror("dup2");
		exit(1);
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
	return (msg_error(sp[0]), NULL);
}
