/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:34:51 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/02 19:28:07 by otamrani         ###   ########.fr       */
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
t_grbg *lst_new(char **p, char *name, char *value)
{
    t_grbg *node;
    node = malloc(sizeof(t_grbg));
    if(!node)
        return (0);
    if(node)
    {
        node->l = p;
        node->p = name;
        node->s = value;
        node->next = NULL;
    }
    return (node);
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

t_env *st_new(char *name, char *value)
{
    char cwd[1024];
    
    if(ft_strcmp(name, "OLDPWD") == 0)
    {
        getcwd(cwd, sizeof(cwd));
        return(ft_lstnew1(name, cwd));
    }
  else if(ft_strcmp(name, "SHLVL") == 0)
        return(ft_lstnew1(name, "1"));
   else if(ft_strcmp(name, "_") == 0)
        return(ft_lstnew1(name, "/usr/bin/"));
    else 
        return(ft_lstnew1(name, value));
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
void new_env(t_env **env)
{
    ft_lstdadd_back1(env, st_new("OLDPWD", ""));
    ft_lstdadd_back1(env, st_new("SHLVL", ""));
    ft_lstdadd_back1(env, st_new("_", ""));
}
t_env *get_environ()
{
    t_env *env;
    extern char	**environ;
    int i;
    char *name;
    char *value;
    i = 0;
    env = NULL;
    if (!environ || !environ[0])
        return(new_env(&env) ,env);
    while(environ[i])
    {
        name = get_name(environ[i]);
        value = get_value(environ[i]);
        ft_lstdadd_back1(&env, st_new(name, value));
        free(name);
        free(value);
        i++;
    }
    return (env);
}
//shlvl=1