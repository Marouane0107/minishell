/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:20 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/17 04:07:43 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

char	*ft_getenv(char *s)
{
	t_env	*tmp;

	tmp = g_lobal.env;
	while (tmp)
	{
		if (tmp && !ft_strcmp(tmp->name, s))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		printf("[%s]\n", g_lobal.pwd);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
