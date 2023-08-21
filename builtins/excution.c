/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:30:04 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/21 17:43:50 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    check_cmd()
{
    
}

int main()
{
    t_env *env;
    
    env = NULL;
    env = get_environ(env);
    // if (argc > 1)
    // {
    //     if (strcmp(argv[1], "env") == 0)
    //         ft_env(*env);
    //     else if (strcmp(argv[1], "pwd") == 0)
    //         pwd();
    //     else if (strcmp(argv[1], "echo") == 0)
    //         echo(argc, argv);
    //     /*check Status of the exit ???*/
    //     else if (strcmp(argv[1], "unset") == 0)
    //         unset(argv, env);
    //     else if (strcmp(argv[1], "exit") == 0)
    //         ft_exit(0);
    // }

    return (0);
}