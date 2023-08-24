/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:13 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/24 21:49:31 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_check(t_data *data)
{
	if (!data || !data->cmd)
		return ;
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
		ft_exit(0);
	// else
	// 	printf("%s: command not found\n", data->cmd[0]);
}

int	main(void)
{
	char	*input;
	t_data	*data;
	t_env	*envi;

	envi = get_environ();
	input = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		data = pparss(input, envi);
		cmd_check(data);
		if(!data)
			continue ;
	}
	return (0);
}