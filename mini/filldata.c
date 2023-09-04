/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filldata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:23:23 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/04 13:53:22 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int openin(t_list *tmp, char **s, int j)
{
    int fd;
    char *here;
    fd = 0;
    if(tmp->token == 5 && !g_lobal.g)
    {
        here = ft_strjoin("/tmp/her", ft_itoa(j));
        fd = open(here, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if(fd == -1)
            return (perror("open"), -3);
        ft_putstr_fd(s[j], fd);
        close(fd);
        fd = open(here, O_RDONLY);
    }
    else if(!g_lobal.g)
    {
        fd = open(tmp->next->content, O_RDONLY);
        if(fd == -1)
        return (perror("open"), -3);
    }
    return (fd);
}

int openout(t_list *lst)
{
    int fd;
    int m;
    char *s;
    m = lst->next->token;
    fd = 1;
    s = lst->next->content;
    if (m == -3)
    {
        printf("bash: %s: ambiguous redirect\n", s);
        return(ft_skip(&lst),1);
    }
    if(!ft_strcmp(s, "\'\'") || !ft_strcmp(s, "\"\""))
        return(printf("bash: : No such file or directory\n"),-3);
    if(lst->token == 3 && !g_lobal.g)
    {
        fd = open(lst->next->content, O_RDWR | O_CREAT, 0644);
        if(fd == -1)
            return (perror("open"), -3);
    }
    else if(lst->token == 4 && !g_lobal.g)
    {
        fd = open(lst->next->content, O_RDWR | O_CREAT | O_APPEND, 0644);
        if(fd == -1)
            return (perror("open"), -3);
    }
    return (fd);
}

void handle_tokens(t_list **lst, t_data **data, char **s, int j)
{
    t_list *tmp;
    t_data *tmp1;
    tmp1 = *data;
    tmp = *lst;
    if(tmp->token == 2 || tmp->token == 5)
    {
        if(tmp1->in > 1)
            close(tmp1->in);
        tmp1->in = openin(tmp, s, j);
        if(tmp1->in == -3)
            ft_skip(lst);
    }
    else if(tmp->token == 4 ||  tmp->token == 3)
    {
        if(tmp1->out > 1)
            close(tmp1->out);
        tmp1->out = openout(tmp);
        if(tmp1->out == -3)
            ft_skip(lst);
    }
   
}

void  add_cmd(char  **cmd, t_list *lst, t_data **tmp)
{
    
    if(lst->token == 0)
    {
        *cmd = ft_strjoin(*cmd, ft_str(-122));
        *cmd = ft_strjoin(*cmd, (lst->content));
    }
    if(*cmd && (lst->next == NULL || lst->token == 1))
    {
        (*tmp)->cmd = ft_split(*cmd, -122);
        free(*cmd);
        *cmd = NULL;
    }
}

void  fill(t_data **data, t_list *lst, char **s)
{
    t_data *tmp;
    char  *cmd;
    int j;
    j = 0;
    cmd = NULL;
    tmp = *data;
    while(lst)
    {
        if(lst->token == 0 || !lst->next || lst->token == 1)
            add_cmd(&cmd, lst, &tmp);
        if(lst->token == 1)
        {
            if(tmp->out == 1)
                tmp->out = -1;
            tmp = tmp->next;
            tmp->in = -2;
        }
        else if(lst->token > 1)
        {
            handle_tokens(&lst, &tmp, s, j);
            if(lst && lst->token == 5)
                j++;
        }
        lst = lst->next;
    }
}