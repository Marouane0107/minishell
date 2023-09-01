/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:50:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/01 20:35:01 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int noptions(t_list *lst)
{
    t_list *tmp;
    int i;
    i = 0;
    tmp = lst;
    while(tmp)
    {
        if(tmp->token == 0)
            i++;
        tmp = tmp->next;
    }
    return (i);
}
void her(int signum)
{
    (void)signum;
     close(0);
     g_lobal.ex = 130;
     g_lobal.g = 1;
     write(1, "\n", 1);
}
char	*stock(char *av, t_list *lst)
{
	char	*line;
    char *all;
    char *tmp;
    int i;

    all = NULL;
    line = NULL;
    i  = dup(0);
    g_lobal.g = 0;
    signal(SIGINT, her);
	while (!g_lobal.g)
	{
		line = readline("> ");
        ft_lstadd(&g_lobal.hold, lst_new(0, line, 0));
    	if (ft_strcmp(line, av) == 0 || !line)
        	break ;
        if(line && lst->next->token != -2)
        {
            quote(line);
            line = check_expend(line, &lst ,0);
            printf("line = [%s]\n", line);
        }
		tmp = ft_strjoin(line, "\n");
        all = ft_strjoin(all, tmp);
	}
    return (dup2(i, 0), close(i), all);
}
 
int count_x(t_list *lst, int j)
{
    t_list *tmp;
    int i;
    i = 0;
    tmp = lst;
    while(tmp)
    {
        if(tmp->token == j)
            i++;
        tmp = tmp->next;
    }
    return (i);
}
char 	**open_here(t_list *lst)
{
	char	**data;
    int i;
    i = 0;
    data = malloc(sizeof(char *) * (count_x(lst, 5) + 1));
    if(!data)
        return (0);
    while(lst && !g_lobal.g)
    {
        if(lst->token == 5)
        {
            data[i] = stock(lst->next->content, lst);
            i++;
        }
        lst = lst->next;
    }
    data[i] = NULL;
    ft_lstadd(&g_lobal.hold, lst_new(data, 0, 0));
    signal(SIGINT, sigint_handler);
    return (data);
}
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
    m = lst->next->token;
    fd = 1;
    if (m == -3)
    {
        printf("bash: %s: ambiguous redirect\n", lst->next->content);
        return(-3);
    }
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
void  allocate(t_data **data, int i)
{
    t_data *tmp;
    (*data)->in = 0;
    (*data)->out = 1; 
    (*data)->cmd = NULL;
    (*data)->next = NULL;
    tmp = *data;
    while(i - 1 > 0)
    {
        ft_lstadd_back2(&tmp, ft_lstnew2(NULL, -1, 1));
        tmp = tmp->next;
        i--;
    }
}

void ft_skip(t_list **lst)
{
    while((*lst))
    {
        if((*lst)->next && (*lst)->next->content[0] == '|')
            break;
        if((*lst)->next == NULL)
            break;
        (*lst) = (*lst)->next;
    }
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
// need free
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
t_data    *convert_lst(t_list *lst)
{
    char **s;
    t_data *tmp;
    t_data *data;
    (void)data;
    data = malloc(sizeof(t_data));
    if(!data)
        return (0);
    allocate(&data, count_x(lst, 1) + 1);
    s = open_here(lst);
    fill(&data, lst, s);
    ffree(s);
    int i = 0;
    tmp = data;
    while(tmp)
    {
         i = 0;
        printf("in = %d\n", tmp->in); 
        printf("out = %d\n", tmp->out); 
        while(tmp->cmd && tmp->cmd[i])
        {
            printf("cmd = [%s]\n", tmp->cmd[i]);
            i++;
        }
        tmp = tmp->next;
    }
    return(data);
}
// " '$USER' "
//  echo ''''''''''$USER''''''''''
// remove space '\" ' " \"\"" split with space
// "$USER""Users/$USER/file""'$USER'"'$USER
//                | not expend
// secend third not expend echo "$USER$USER$USER"
// echo " $USER  "'$PWD'	no exp
// << lgsd
// here_doc: gsgfd
// here_doc: gfs
// here_doc: gsdfgetkonjr
// here_doc: lgsd
// minishell$ gsag << l
// here_doc: gasohkfd
// here_doc: gsahojfdal
// here_doc: fjoa
// here_doc: l
// minishell$ gsg < "l"
// open: Permission denied
// minishell$ gsg << "l"
// here_doc: gsafhf
// here_doc: shfahfa
// here_doc: shfa
// here_doc: gfa
// here_doc: l
// minishell$ 
