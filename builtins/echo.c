/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:50:09 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/23 00:51:38 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/minishell.h"

void    ft_echo(t_data *data)
{
    int i;
    int f;

    i = 1;
    f = 0;
    if (ft_strcmp(data->cmd[i], "-n") == 0)
    {
        i++;
        f = 1;
    }
    while (data->cmd && data->cmd[i])
    {
        printf("%s",data->cmd[i]);
        i++;
        if (data->cmd[i])
            printf(" ");
    }
    if (f != 1)
        printf("\n");
}
