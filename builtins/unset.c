/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 09:36:19 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/21 10:45:30 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    unset(char *argv[], t_env **env)
{
    int i;
    t_env *tmp;

    i = 1;
    tmp = *env;
while (tmp && argv[i])
    {
       
        if (ft_strcmp((tmp)->next->name, argv[i]) == 0)
        {
            tmp->next = (tmp)->next->next;
            i++;
        }
        tmp = (tmp)->next;
    }
}