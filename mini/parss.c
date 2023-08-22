/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:51:09 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/22 22:29:20 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *treatin(char *s,t_env *env)
{
	int		i;
	t_list *lst;
	// int		j;
	char	**p;
	i = 0;
	lst = NULL;
	p = ft_split(s, ' ');
	// j = 0;
	i = 0;
	while (p[i])
	{
		if (!detach_separted(p[i], env, &lst))
			return (0);
		i++;
	}
	if (end_struct(&lst) > 0)
		return (ft_putstr_fd("minishell$ syntax errorF\n", 2), NULL);
	return (lst);
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
char	*quote(char *in)
{
	int	i;
	int	m;
	int	j;

	m = 0;
	i = 0;
	j = 0;
	while (in[i])
	{
		if (in[i] == '\"' && j % 2 == 0)
			m++;
		if (in[i] == '\'' && m % 2 == 0)
			j++;
		if (ins(in[i], m, j))
		{
			in[i] = in[i] * -1;
		}
		i++;
	}
	if (j % 2 != 0 || m % 2 != 0)
		return (write(2, "minishell$ syntax error Q\n", 25), NULL);
	return (in);
}
int	fil_env(t_list **lst)
{
	extern char	**environ;
	int			i;

	i = 0;
	*lst = malloc(sizeof(t_list));
	while (environ[i])
		i++;
	(*lst)->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		(*lst)->env[i] = ft_strdup(environ[i]);
		i++;
	}
	(*lst)->env[i] = NULL;
	(*lst)->content = NULL;
	(*lst)->next = NULL;
	return (1);
}
void ft_free_linkdlist(t_data *data, t_list *lst)
{
	t_list *tmp;
	t_data *tmp2;
	tmp = lst;
	tmp2 = data;
	while (tmp)
	{
		lst = lst->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = lst;
	}
	while (tmp2)
	{
		data = data->next;
		free(tmp2->cmd);
		tmp2->cmd = NULL;
		free(tmp2);
		tmp2 = data;
	}
}

t_data	*pparss(char *input, t_env *env)
{
	t_data *data;
	// int	i;
	t_list *tmp;
	// i = 0;
	if (!input || !*input)
		return (0);
	if (!quote(input))
		return (0);
	tmp = treatin(input, env);
	if (!tmp)
		return (0);
	data = convert_lst(tmp);
	// while (tmp)
	// {
	// 	printf("%s\n", (tmp)->content);
	// 	printf("%d\n", (tmp)->token);
	// 	tmp = (tmp)->next;
	// }
	return(data);
}
// syntax error $cs'\'
// syntax error $cs'!'
// '' `` "" in last word
//`` in word
//"ls $"