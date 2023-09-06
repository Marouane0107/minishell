/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:50:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/05 13:17:12 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_error(t_list *lst)
{
	int	i;

	i = end_struct(&lst);
	if (i == 1)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	if (lst)
		free_lst(lst);
}

int	ins(char c, int m, int j)
{
	if (m % 2 != 0 && c != '\"')
		return (1);
	else if (j % 2 != 0 && c != '\'')
		return (1);
	else
		return (0);
}
int noption(t_list **lst)
{

    int i;
    i = 0;
    if((*lst) && (*lst)->token == 1)
        (*lst) = (*lst)->next;
    while((*lst))
    {
        if((*lst)->token == 1)
            return(i);
        (*lst) = (*lst)->next;
        i++;
    }
    return(i);
}
void  allocate(t_data **data, int i,t_list *tmp1)
{
    int j;
    j = 0;
    while(i > 0)
    {
        j = noption(&tmp1);
        ft_lstadd_back2(data, ft_lstnew2(0, 1, j + 1));
        i--;
    }
}

t_data    *convert_lst(t_list *lst)
{
    char **s;
    t_list *tm;
    t_data *tmp;
    t_data *data;
    (void)data;
    data = NULL;
    tm = lst;
    allocate(&data, count_x(lst, 1), tm);
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
///////////////////////////////////////////////////////
// minishell$ > ""
// bash: : No such file or directory
// in = 0
// out = 1
// minishell$ > "" | ls
// bash: : No such file or directory
// in = 0
// out = -1
// in = -2
// out = 1
// cmd = [ls]
// minishell$ > '' |  ls
// bash: : No such file or directory
// in = 0
// out = -1
// in = -2
// out = 1
// cmd = [ls]
// minishell$ "" | ''
// in = 0
// out = -1
// cmd = ['']
// in = -2
// out = 1
// cmd = ['']
// minishell$ ls ""
// in = 0
// out = 1
// cmd = [ls]
// cmd = ['']
// minishell$ ls ''
// in = 0
// out = 1
// cmd = [ls]
// cmd = ['']
// minishell$ pwdd
// in = 0
// out = 1
// cmd = [pwdd]
// minishell$ ls
// in = 0
// out = 1
// cmd = [ls]
// minishell$ 
