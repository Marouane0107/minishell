/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:28:43 by maouzal           #+#    #+#             */
/*   Updated: 2023/08/20 20:01:09 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void    cd(char *path)
{
    if (!path)
        path = getenv("HOME");
    if (chdir(path) == -1 || access(path, F_OK) == -1)
        printf("cd: %s: No such file or directory\n", path);
    else if (access(path, (R_OK || W_OK) && X_OK) == -1)
        printf("cd: %s: Permission denied\n", path);
    else
        chdir(path);
    
}

// void    set_new_path(char *path)
// {
//     char *new_path;
//     char *old_path;

//     old_path = getcwd(NULL, 0);
//     new_path = ft_strjoin(old_path, "/");
//     new_path = ft_strjoin(new_path, path);
//     cd(new_path);
//     free(new_path);
//     free(old_path);
// }