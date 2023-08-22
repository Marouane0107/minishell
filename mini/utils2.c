/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:56:20 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/22 22:28:15 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int adge_case(char *s, int j, char *q)
{
	if(q[j] < 0)
		return(0);
	if ((s[j] == '$' && s[j + 1] == '\"' && s[j + 2] != 0))
			return(1);
	if ((s[j] == '$' && s[j + 1] == '\'' && s[j + 2] != 0))
			return(1);
		return(0);
}
int	get_exp(char *s, int j, char *q, t_list *lst)
{
	int	i;

	i = 0;
	if(j - 1 >= 0 && s[j] == '$' && s[j - 1] == '\'' && lst->token != 5)
		return (0);
	if(j - 1 >= 0 && s[j] == '$')
	{
		if(s[j - 1] == '$' || q[j - 1] < 0)
			return (0);
	}
	if (s[j] == '$')
	{
		j++;
	while (s[j] && s[j] != ' ' && s[j] != '\t')
	{
		if ((s[j] >= 33 && s[j] <= 47) || (s[j] >= 58 && s[j] <= 64))
			break ;
		if ((s[j] >= 91 && s[j] <= 96) || (s[j] >= 123 && s[j] <= 126))
			break ;
		j++;
		i++;
	}
	}
	return (i);
}
char	*searsh_env(char *c, t_env *env)
{
	t_env *tmp;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, c))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
char	*ft_str(char s)
{
	char	*c;

	c = malloc(sizeof(char) * 2);
	c[0] = s;
	c[1] = '\0';
	return (c);
}
char	*check_expend(char *s, t_list **lst, int j)
{
	int		i;
	char	*c;
	char	*ex;
	char	*all;
	char *q;

	i = 0;
	all = NULL;
	q = quote(ft_strdup(s));
	while (s[i])
	{
		if(adge_case(s, i, q) && j)
			i++;
		if (get_exp(s ,i,q, *lst) && j != 2)
		{
			c = ft_substr(s, i + 1, get_exp(s ,i,q, *lst));
			ex = searsh_env(c, (*lst)->envi);
			all = ft_strjoin(all, ex);
			i += ft_strlen(c);
		}
		else if ((q[i] != '\'' && q[i] != '\"') || !j)
			all = ft_strjoin(all, ft_str(s[i]));
		i++;
	}
	return(all);
}
int ft_word(char *s, t_env *env, t_list **lst)
{
	char *wexp;

	quote(s);
	if(end_struct(lst) == 5)
		return(ft_lstadd_back(lst, ft_lstnew(check_expend(s, lst , 2), -1, env)), 1);
	wexp = check_expend(s, lst, 1);
	if(end_struct(lst) > 1)
		ft_lstadd_back(lst, ft_lstnew(wexp, -1, env));
	else
		ft_lstadd_back(lst, ft_lstnew(wexp, 0, env));
	if ((*lst)->token == 1)
		return(ft_putstr_fd("syntax error near |", 2), 0);
	return(1);
}
void	putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}