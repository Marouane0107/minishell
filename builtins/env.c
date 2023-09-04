/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 09:53:38 by maouzal           #+#    #+#             */
/*   Updated: 2023/09/04 14:36:50 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_env(t_data *data)
{
    t_env *tmp;
    
    if (data->cmd[1])
    {
        ft_putstr_fd("env: ", 1);
        ft_putstr_fd(data->cmd[1], 1);
        ft_putstr_fd(": No such file or directory\n", 1);
        return ;
    }
    tmp = g_lobal.env;
    while(tmp)
    {
        if(tmp->value)
        {
            ft_putstr_fd(tmp->name, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(tmp->value, 1);
            ft_putstr_fd("\n", 1);
        }
        tmp = tmp->next;
    }
}
