/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:13 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/04 21:00:47 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int status;
t_global g_lobal;

int	main()
{	
	g_lobal.i = 1;
	g_lobal.j = 0;
	parss();
	return (0);
}