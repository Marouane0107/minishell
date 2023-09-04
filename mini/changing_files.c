/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:25:08 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/03 19:07:55 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_close_file(t_data *data)
{
	if (!data)
		return ;
	if (data->out > 1)
		close(data->out);
	if (data->in > 0)
		close(data->in);
}

void	out_in_file(t_data *data)
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
}

void    parent(int fd[2])
{
	if (dup2(fd[0], 0) == -1)
		perror("dup2");
	ft_close_pipe(fd);
}

void child(t_data *data, int fd[2])
{
	out_in_file(data);
	if (data->out == -1)
	{
		if (dup2(fd[1], 1) == -1)
			perror("dup2");
		ft_close_pipe(fd);
		if(cmd_check(data) > 0)
			exec_cmd(data);
		exit(0);
	}
	else if (data->out != -1)
	{
		if (dup2(1, fd[1]) == -1)
			perror("dup2");
		ft_close_pipe(fd);
		if(cmd_check(data) > 0)
			exec_cmd(data);
		exit(0);
	}
}
