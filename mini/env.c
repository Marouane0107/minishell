/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:34:51 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/28 00:15:00 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


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
        node->name = ft_strdup(name);
        node->value = ft_strdup(value);
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
    name = malloc(sizeof(char) * i + 1);
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
    value = malloc(sizeof(char) * (i - j + 1));
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

t_list *get_environ(t_list **lst)
{
    extern char	**environ;
    int i;
    char *name;
    char *value;
    i = 1;
    name = get_name(environ[i]);
    value = get_value(environ[i]);
    (*lst)->content = NULL;
	(*lst)->next = NULL;
    (*lst)->envi = ft_lstnew1(name, value);
    free(name);
    free(value);
    while(environ[i])
    {
        name = get_name(environ[i]);
        value = get_value(environ[i]);
        ft_lstdadd_back1(&(*lst)->envi, ft_lstnew1(name, value));
        free(name);
        free(value);
        i++;
    }
    return (*lst);
}
//shlvl=1