/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 09:53:38 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/22 13:52:02 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_env(t_data *data)
{
    while(data->env)
    {
        ft_putstr_fd(data->env->name, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(data->env->value, 1);
        ft_putstr_fd("\n", 1);
        data->env = data->env->next;
    }
}
