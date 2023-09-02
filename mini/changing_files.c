/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:25:08 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/02 18:41:52 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_close(t_data *data, int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	if (data && data->out > 1)
		close(data->out);
	if (data && data->in > 0)
		close(data->in);
}

void    parent(t_data *data, int fd[2])
{
	(void)data;
	if (dup2(fd[0], 0) == -1)
		perror("dup2");
	close(fd[1]);
	close(fd[0]);
	// if (data->in > 0)
	// 	close(data->in);
}

void child(t_data *data, int fd[2])
{
	if (data->out > 1)
	{
		if (dup2(data->out, 1) == -1)
			perror("dup2");
	}
	if (data->in > 0)
	{
		if (dup2(data->in, 0) == -1)
			perror("dup2");
	}
	if (data->out == 0)
	{
		if (dup2(fd[1], 1) == -1)
			perror("dup2");
		close(fd[0]);
		close(fd[1]);
		cmd_check(data);
		exit(0);
	}
	else if (data->out != 0)
	{
		if (dup2(1, fd[1]) == -1)
			perror("dup2");
		close(fd[0]);
		close(fd[1]);
		cmd_check(data);
		exit(0);
	}
	// if (data->out > 1)
	// 	close(data->out);
}
