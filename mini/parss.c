/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:51:09 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/08 15:30:38 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_data	*distribut(char *input)
{
	t_list	*lst;
	t_data	*data;

	data = NULL;
	lst = NULL;
	if (!*input)
		return (0);
	if (!quote(input))
		return (msg_error(lst), NULL);
	lst = treatin(input, lst);
	if (!lst)
		return (free_lst(lst), NULL);
	data = convert_lst(lst);
	free_lst(lst);
	lst = NULL;
	return (data);
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
	int		x;
	int		y;
	t_data	*data;

	data = NULL;
	g_lobal.env = get_environ();
	input = NULL;
	x = dup(0);
	y = dup(1);
	g_lobal.ex = 0;
	while (1)
	{
		if (input)
			free(input);
		dup2(x, 0);
		dup2(y, 1);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		g_lobal.g = 0;
		if (!input)
			exit(g_lobal.ex);
		add_history(input);
		data = distribut(input);
		if (data && !g_lobal.g)
			ft_exec(data);
		if (data)
		{
			free_data(data);
			data = NULL;
		}
		if (!data)
			continue ;
	}
}

// cd .. leaks

// a="ls -l"
// export a=ls | export a+=l == a=l ??
// echo ad >a
// exit 2
// rm -rf ./ pwd
// bash ./minishel PATH
// bash -> ./minishell !env
// $P pwd export export PATH="" export export export declare -x PWD=""
// export declare -x PWD="/nfs/homes/otamrani"
// cd .. pwd
//////////////////////////////
// cat gsgrt & cat | fdsa -> exit status echo $?
// env -i minishell cmd not work
//_="/usr/bin/" add command exec in it
////echo ad >a
// tty
// cat l
// in = 0
// out = 1
// cmd = [cat]
// cmd = [l]
// f
// f
// command not found
