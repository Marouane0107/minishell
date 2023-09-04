/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openherd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:12:10 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/05 00:37:00 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

void her(int signum)
{
    (void)signum;
     close(0);
     g_lobal.ex = 130;
     g_lobal.g = 1;
     write(1, "\n", 1);
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
        if(tmp->token == j || tmp->next == NULL)
            i++;
        tmp = tmp->next;
    }
    return (i);
}