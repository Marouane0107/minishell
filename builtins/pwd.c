/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:20 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/22 13:52:09 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free(pwd);
}