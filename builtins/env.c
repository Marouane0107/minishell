/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 09:53:38 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/20 08:52:30 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    env(t_env *env)
{
    env = get_environ(env);
    while(env)
    {
        printf("%s", env->name);
        printf("=");
        printf("%s", env->value);
        printf("\n");
        env = env->next;
    }
}
