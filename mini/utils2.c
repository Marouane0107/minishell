/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:56:20 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/01 00:54:08 by otamrani         ###   ########.fr       */
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
int check_single(char *s,int j)
{
	int i;
	int k;
	k= 0;
	i = 0;
	while(s[i] && j > i)
	{
		if(s[i] == '\'')
			k++;
		i++;
	}
	if(k % 2 != 0)
		return(1);
	return(0);

}
int	get_exp(char *s, int j, char *q, int m)
{
	int	i;

	i = 0;
	if(m != 0)
	{
		printf("gdf\n");
	if((s[j] == '$' && check_single(q, j)))
	{
		// if(lst && lst->token != 5)
			return(0);
	}
	}
	if(j - 1 >= 0 && s[j] == '$')
	{
		if(s[j - 1] == '$')
			return (0);
	}
	if (s[j] == '$')
	{
		j++;
	while (s[j] && s[j] != ' ' && s[j] != '\t' && s[j] != '`')
	{
		if ((s[j] >= 33 && s[j] <= 47) || (s[j] >= 58 && s[j] <= 64))
			break ;
		if ((s[j] >= 91 && s[j] <= 94) || (s[j] >= 123 && s[j] <= 126))
			break ;
		j++;
		i++;
	}
	}
	return (i);
}
char	*searsh_env(char *c)
{
	t_env *tmp;

	tmp = g_lobal.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, c))
			return (ft_strdup(tmp->value));
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
	char	*all;
	char *q;
	i = 0;
	(void)lst;
	all = ft_strdup("");
	q = ft_strdup(s);
	quote(q);
	while (q[i])
	{
		if(adge_case(q, i, s) && j)
			i++;
		else if (get_exp(q ,i,s, j) && j != 2)
		{
			c = ft_substr(q, i + 1, get_exp(q ,i,s, j));
			all = ft_strjoin(all, searsh_env(c));
			i += ft_strlen(c);
		}
		else if ((s[i] != '\'' && s[i] != '\"') || !j)
				all = ft_strjoin(all, ft_str(q[i]));
		i++;
	}
	ft_lstadd(&g_lobal.hold, lst_new(0, all,0));
	return(free(q), all);
}
void swap(char *s, int i)
{
	while(s[i])
	{
		s[i] = s[i + 1];
		i++;
	}
}
void ex_status(char **s)
{
	int i;
	int j;
	char *c;
	char *tmp;
	i = 0;
	j = 1;
	if (!s || !(*s))
		return ;
	while((*s)[i])
	{
		
		if((*s)[i] == '$' && (*s)[i + 1] == '?' && (j % 2))
		{
			c =  ft_itoa(g_lobal.ex);
			tmp = ft_strjoin(c, ft_substr((*s), i + 2, ft_strlen((*s))));
			(*s) = ft_strjoin(ft_substr((*s), 0,i), tmp);
		}
		if((*s)[i] == '$' && (*s)[i + 1] == '$')
			j++;
		i++;
	}
	ft_lstadd(&g_lobal.hold, lst_new(0, c, 0));
}
int ft_word(char *s, t_list **lst)
{
	char *wexp;
	if(end_struct(lst) == 5)
		{
			wexp = check_expend(s,lst, 2);
			if(ft_strchr(s, '\'') || ft_strchr(s, '\"'))
			{
				// return(ft_lstadd_back(lst, ft_lstnew(check_expend(s, lst, 2), -2)) , 1);
				ft_lstadd_back(lst, ft_lstnew(wexp, -2));
				return(1);
			}
		// return(ft_lstadd_back(lst, ft_lstnew(check_expend(s, lst , 2), -1)), 1);
			ft_lstadd_back(lst, ft_lstnew(wexp, -1));
			return(1);
		}
	wexp = check_expend(s, lst, 1);
	if(!(*wexp) && (ft_strchr(s, '\'') || ft_strchr(s, '\"')))
		wexp = ft_strdup("''");
	ex_status(&wexp);
	if(end_struct(lst) > 1)
		ft_lstadd_back(lst, ft_lstnew(wexp, -1));
	else
		ft_lstadd_back(lst, ft_lstnew(wexp, 0));
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