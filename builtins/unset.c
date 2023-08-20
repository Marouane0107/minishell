/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 09:36:19 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/20 10:51:14 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    unset(int argc, char *argv[], t_env **env)
{
    int     i;
    int     j;
    char    *nom;

    i = 0;
    while (*env)
    {
        j = 0;
        while ((*env)->name[j] != '=')
        {
            nom[j] = (*env)->name[j];
            j++;
        }
        if (ft_strcmp(nom, argv[i]) == 0)
        {
            
        }
    }
}

void    remove_node(t_env **env)
{
    t_env *head;
    t_env *tmp;

    head = *env;
    tmp = head->next;
    head->next = tmp->next;
    free(tmp);
}