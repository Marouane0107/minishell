/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:13 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/22 13:36:54 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_check(t_data *data)
{
	if (ft_strcmp(data->cmd[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->cmd[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->cmd[0], "env") == 0)
		ft_env(data);
}

int	main(void)
{
	char	*input;
	t_data	*data;

	input = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		data = pparss(input);
		cmd_check(data);
		if(!data)
			continue ;
	}
	return (0);
}