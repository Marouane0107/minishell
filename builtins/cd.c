/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:28:43 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/23 22:32:38 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_setenv(t_data **data, char *s, char *path)
{
	t_env	*tmp;

	tmp = (*data)->env;
	while (tmp && path)
	{
		if (!ft_strcmp(tmp->name, s))
		{
			tmp->value = NULL;
			tmp->value = path;
			break;
		}
		tmp = tmp->next;
	}
	
}

void    change_path(t_data *data, char *path)
{
	char	old_path[BUFFER_SIZE];
	char	new_path[BUFFER_SIZE];

	//gitenv
	getcwd(old_path, sizeof(old_path));
	if (!chdir(path))
	{
		getcwd(new_path, sizeof(new_path));
		ft_setenv(&data, "PWD", new_path);
		ft_setenv(&data, "OLDPWD", old_path);
	}
}

void    ft_cd(t_data *data)
{

	if (!(data->cmd[1]) || !(ft_strcmp(data->cmd[1], "~")))
		change_path(data, getenv("HOME"));
	else if (access(data->cmd[1], X_OK) == -1 || access(data->cmd[1], F_OK) == -1)
		printf("cd: %s: No such file or directory\n", data->cmd[1]);
	else if (access(data->cmd[1], F_OK) == 0 && access(data->cmd[1], X_OK) == -1)
		printf("cd: %s: Not a directory\n", data->cmd[1]);
	else if (access(data->cmd[1], F_OK) == 0 && access(data->cmd[1], X_OK) == 0)
		change_path(data, data->cmd[1]);
	else
		printf("cd: %s: No such file or directory\n", data->cmd[1]);
		
}
