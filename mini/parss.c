/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:51:09 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/16 21:49:23 by otamrani         ###   ########.fr       */
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
	{
		g_lobal.ex = 0;
		return (0);
	}
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

void ft_tfree(t_data *data , char *in)
{
	if (data)
		{
			free_data(data);
			data = NULL;
		}
		if(in)
			free(in);
}

void	parss(t_data *data, char *input)
{
	int		x;
	int		y;

	x = dup(0);
	y = dup(1);
	while (1)
	{
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
		ft_tfree(data, input);
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
// f		if (data && !g_lobal.g)
// command not found
////////////////////////
//bash: cd: ./minishell: Not a directory
// + like
/////////////////////////////////////////
// export a="ls -l"
// minishell$ $a
// total 1696
// -rw-r--r-- 1 otamrani 2019    1870 Sep 16 16:53 changing_files.c
// -rw-r--r-- 1 otamrani 2019    9776 Sep 16 17:16 chaexport a="ls -l"
// minishell$ $a
// total 1696
// -rw-r--r-- 1 otamrani 2019    1870 Sep 16 16:53 changing_files.c
// -rw-r--r-- 1 otamrani 2019    9776 Sep 16 17:16 changing_files.o
// -rw-r--r-- 1 otamrani 2019    2912 Sep 16 16:53 excution.c
// -rw-r--r-- 1 otamrani 2019   18496 Sep 16 17:16 excution.o
// -rw-r--r-- 1 otamrani 2019    2628 Sep 16 16:53 excution_utils.c
// -rw-r--r-- 1 otamrani 2019   14304 Sep 16 17:16 excution_utils.o
// -rw-r--r-- 1 otamrani 2019    3275 Sep 16 16:53 filldata.c
// -rw-r--r-- 1 otamrani 2019   19864 Sep 16 17:16 filldata.o
// -rw-r--r-- 1 otamrani 2019    1583 Sep 16 16:53 free.c
// -rw-r--r-- 1 otamrani 2019    8568 Sep 16 17:16 free.o
// -rw-r--r-- 1 otamrani 2019    2446 Sep 16 16:53 get_env.c
// -rw-r--r-- 1 otamrani 2019   14416 Sep 16 17:16 get_env.o
// drwxr-xr-x 2 otamrani 2019    4096 Sep 16 17:16 libft
// -rw-r--r-- 1 otamrani 2019    2130 Sep 16 16:53 linkd_list.c
// -rw-r--r-- 1 otamrani 2019    8760 Sep 16 17:16 linkd_list.o
// -rw-r--r-- 1 otamrani 2019    1127 Sep 16 16:53 main.c
// -rw-r--r-- 1 otamrani 2019    6000 Sep 16 17:16 main.o
// -rw-r--r-- 1 otamrani 2019     663 Sep 16 16:53 Makefile
// -rwxr-xr-x 1 otamrani 2019 1424144 Sep 16 17:16 minishell
// -rw-r--r-- 1 otamrani 2019    5053 Sep 16 16:53 minishell.h
// -rw-r--r-- 1 otamrani 2019    2426 Sep 16 16:53 openherd.c
// -rw-r--r-- 1 otamrani 2019   12624 Sep 1type 'char *'6 17:16 openherd.o
// -rw-r--r-- 1 otamrani 2019    3176 Sep 16 17:03 parss.c
// -rw-r--r-- 1 otamrani 2019   13512 Sep 16 17:16 parss.o
// -rw-r--r-- 1 otamrani 2019    2482 Sep 16 16:53 utils1.c
// -rw-r--r-- 1 otamrani 2019   11536 Sep 16 17:16 utils1.o
// -rw-r--r-- 1 otamrani 2019    3100 Sep 16 16:53 utils2.c
// -rw-r--r-- 1 otamrani 2019   15104 Sep 16 17:16 utils2.o
// -rw-r--r-- 1 otamrani 2019    3290 Sep 16 16:53 utils3.c
// -rw-r--r-- 1 otamrani 2019   11128 Sep 16 17:16 utils3.o
// -rw-r--r-- 1 otamrani 2019    1620 Sep 16 16:53 utils5.c
// -rw-r--r-- 1 otamrani 2019    6152 Sep 16 17:16 utils5.o
// -rw-r--r-- 1 otamrani 2019    2335 Sep 16 17:08 utils6.c
// -rw-r--r-- 1 otamrani 2019   12272 Sep 16 17:16 utils6.o
// -rw-r--r-- 1 otamrani 2019    2435 Sep 16 16:53 utils.c
// -rw-r--r-- 1 otamrani 2019   13824 Sep 16 17:16 utils.o
// minishell$ '$a'
// $a: command not found
// minishell$ export a=l
// a=l: command not found
// minishell$ export a=l
// a=l: command not found
// minishell$ export a =p
// =p: command not found
// minishell$ export a
// a: command not found
// minishell$ export l=p
// l=p: command not found
// minishell$ ls
// changing_files.c  excution_utils.o  get_env.c	  main.c       openherd.c  utils1.o  utils5.c  utils.o
// changing_files.o  filldata.c	    get_env.o	  main.o       openherd.o  utils2.c  utils5.o
// excution.c	  filldata.o	    libft	  Makefile     parss.c	   utils2.o  utils6.c
// excution.o	  free.c	    linkd_list.c  minishell    parss.o	   utils3.c  utils6.o
// excution_utils.c  free.o	    linkd_list.o  minishell.h  utils1.c    utils3.o  utils.c
// minishell$ echo $?
// 0: command not found
// -rw-r--r-- 1 otamrani 2019    8568 Sep 16 17:16 free.o
// -rw-r--r-- 1 otamrani 2019    2446 Sep 16 16:53 get_env.c
// -rw-r--r-- 1 otamrani 2019   14416 Sep 16 17:16 get_env.o
// drwxr-xr-x 2 otamrani 2019    4096 Stype 'char *' 2019    1620 Sep 16 16:53 utils5.c
// -rw-r--r-- 1 otamrani 2019    6152 Sep 16 17:16 utils5.o
// -rw-r--r-- 1 otamrani 2019    2335 Sep 16 17:08 utils6.c
// -rw-r--r-- 1 otamrani 2019   12272 Sep 16 17:16 utils6.o
// -rw-r--r-- 1 otamrani 2019    2435 Sep 16 16:53 utils.c
// -rw-r--r-- 1 otamrani 2019   13824 Sep 16 17:16 utils.o
// minishell$ '$a'
// $a: command not found
// minishell$ export a=l
// a=l: command not found
// minishell$ export a=l
// a=l: command not found
// minishell$ export a =p
// =p: command not found
// minishell$ export a
// a: command not found
// minishell$ export l=p
// l=p: command not found
// minishell$ ls
// changing_files.c  excution_utils.o  get_env.c	  main.c       openherd.c  utils1.o  utils5.c  utils.o
// changing_files.o  filldata.c	    get_env.o	  main.o       openherd.o  utils2.c  utils5.o
// excution.c	  filldata.o	    libft	  Makefile     parss.c	   utils2.o  utils6.c
// excution.o	  free.c	    linkd_list.c  minishell    parss.o	   utils3.c  utils6.o
// excution_utils.c  free.o	    linkd_list.o  minishell.h  utils1.c    utils3.o  utils.c
// minishell$ echo $?
// 0: command not found
//////////////////////////////
//rm -rf ../../../a
//'' && '' in ex