/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:22:40 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/20 08:51:31 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

t_env *ft_lstdadd_back1(t_env **lst, t_env *new)
{
    t_env *tmp;
    if(!lst || !new)
        return (0);
    if(!(*lst))
        *lst = new;
    else
    {
        tmp = *lst;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (new);
}

t_env *ft_lstnew1(char *name, char *value)
{
    t_env *node;
    node = malloc(sizeof(t_env));
    if(!node)
        return (0);
    if(node)
    {
        node->name = name;
        node->value = value;
        node->next = NULL;
    }
    return (node);
}

char *get_name(char *str)
{
    int i;
    char *name;
    i = 0;
    while(str[i] != '=')
        i++;
    name = malloc(sizeof(char) * i);
    i = 0;
    while(str[i] != '=')
    {
        name[i] = str[i];
        i++;
    }
    name[i] = '\0';
    return (name);
}

char *get_value(char *str)
{
    int i;
    int j;
    char *value;
    i = 0;
    while(str[i] != '=')
        i++;
    i++;
    j = i;
    while(str[i])
        i++;
    value = malloc(sizeof(char) * (i - j));
    i = 0;
    while(str[j])
    {
        value[i] = str[j];
        i++;
        j++;
    }
    value[i] = '\0';
    return (value);
}

t_env   *get_environ(t_env *envi)
{
    extern char    **environ;
    int i;
    char *name;
    char *value;
    i = 1;
    envi = ft_lstnew1(get_name(environ[0]), get_value(environ[0]));
    while(environ[i])
    {
        name = get_name(environ[i]);
        value = get_value(environ[i]);
        ft_lstdadd_back1(&envi, ft_lstnew1(name, value));
        i++;
    }
    return (envi);
}
