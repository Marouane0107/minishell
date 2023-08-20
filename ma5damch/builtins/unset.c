/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 09:36:19 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/20 13:58:04 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    unset(char *argv[], t_env **env)
{
    int     i;
    int     j;
    char    *nom;

    i = 0;
    *env = get_eviron(*env);

    nom = malloc(sizeof(char) * ft_strlen((*env)->name));
    while (*env)
    {
        j = 0;
        while ((*env)->name[j] != '=' && (*env)->name[j] != '\0')
        {
            nom[j] = (*env)->name[j];
            j++;
        }
        if (ft_strcmp(nom, argv[i]) == 0)
        {
            remove_node(env, nom);
        }
        free (nom);
        i++;
    }
}

void    remove_node(t_env **env, char *name)
{
    t_env *tmp;
    t_env *holder;
    
    if (!(*env))
        return ;
    tmp = *env;
    while (*env)
    {
        if ((*env)->name == name)
        {
            holder = *env;
            *env = (*env)->next;
            free(holder);
        }
        else
            *env = (*env)->next;
    }
    *env = tmp;
}

int main(int ac, char* av[])
{
    t_env *env;

    if (ac != 1)
        unset(av, &env);

    return (0);
}