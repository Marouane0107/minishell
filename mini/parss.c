/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:51:09 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/21 18:20:47 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*treatin(char *s)
{
	int		i;
	// int		j;
	char	**p;
	t_list	*lst;

	i = 0;
	lst = malloc(sizeof(t_list));
		if(!lst)
			return (0);
	lst = get_environ(&lst);
	p = ft_split(s, ' ');
	// j = 0;
	while (p[i])
	{
		if (!detach_separted(p[i], &lst))
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
int	pparss(char *input)
{
	t_list	*lst;
	// int	i;
	
	// i = 0;
	if (!input || !*input)
		return (0);
	if (!quote(input))
		return (0);
	lst = treatin(input);
	if (!lst)
		return (0);
	convert_lst(lst);
	// while (lst)
	// {
	// 	printf("%s\n", (lst)->content);
	// 	printf("%d\n", (lst)->token);
	// 	lst = (lst)->next;
	// }
	return (1);
}
void	parss(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		if (!pparss(input))
			continue ;
	}
}
// syntax error $cs'\'
// syntax error $cs'!'
// '' `` "" in last word
//`` in word
//"ls $"