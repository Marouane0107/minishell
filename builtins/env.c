/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 09:53:38 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/21 15:46:53 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    ft_env(t_env *env)
{
    while(env)
    {
        ft_putstr_fd(env->name, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(env->value, 1);
        ft_putstr_fd("\n", 1);
        env = env->next;
    }
}
