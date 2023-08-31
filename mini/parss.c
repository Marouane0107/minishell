/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:51:09 by otamrani          #+#    #+#             */
/*   Updated: 2023/08/31 23:55:18 by otamrani         ###   ########.fr       */
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
t_list	*treatin(char *s, t_list *lst)
{
	int		i;
	char	**p;

	i = 0;
	p = ft_split(s, ' ');
	while (p[i])
	{
		if (!detach_separted(p[i], &lst))
			return (0);
		i++;
	}
	if (end_struct(&lst) > 0)
		return (msg_error(lst), NULL);
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

int	quote(char *in)
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
		return (0);
	return (1);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = (env);
		(env) = (env)->next;
		if (env)
		{
			free(tmp->name);
			free(tmp->value);
		}
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data;
		data = data->next;
		// if(data)
		// {
		// 	ffree(tmp->cmd);
		// }
		free(tmp);
	}
}

void	free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp)
		{
			if (tmp->content && *tmp->content)
				free(tmp->content);
		}
		free(tmp);
	}
}

int	pparss(char *input)
{
	t_list	*lst;
	t_data	*data;

	lst = NULL;
	// input free
	if (!*input)
		return (0);
	// input free
	if (!quote(input))
		return (msg_error(lst), 0);
	lst = treatin(input, lst);
	if (!lst)
		return (free_lst(lst), 0);
	data = convert_lst(lst);
	free_lst(lst);
	free_data(data);
	lst = NULL;
	// while (lst)
	// {
	// 	printf("--%s+\n", (lst)->content);
	// 	printf("---%d++\n", (lst)->token);
	// 	lst = (lst)->next;
	// }
	return (1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_lobal.ex = 130;
	if (!g_lobal.g)
		ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);	
	rl_on_new_line();
	rl_redisplay();
}

void	parss(void)
{
	char	*input;

	g_lobal.env = get_environ();
	input = NULL;
	while (1)
	{
		if (input)
			free(input);
		g_lobal.ex = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		g_lobal.g = 0;
		if (!input)
			exit(0);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
		if (!pparss(input))
			continue ;
	}
}
// syntax error $cs'\'
// syntax error $cs'!'
// '' `` "" in last word
//`` in word
//"ls $"