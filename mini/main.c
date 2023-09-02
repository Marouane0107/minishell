/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:13 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/02 19:05:05 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int status; 
t_global g_global;
int	main(void)
{
	char	*input;
	t_data	*data;
	t_env	*envi;
	int x;
	int y;

	g_global.env = get_environ();
	envi = g_global.env;
	input = NULL;
	x = dup(0);
	y = dup(1);
	while (1)
	{
		data->f = 0;
		dup2(x, 0);
		dup2(y, 1);
		input = readline("minishell$ ");
		add_history(input);
		data = pparss(input, envi);
		if (data)
			ft_exec(data);
		if(!data)
			continue ;
	}
	return (0);
}
