/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:07:33 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/13 23:19:34 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <unistd.h>

void		putstr_fd(char *s, int fd, char *m);
size_t		ft_strlen(const char *s);
char		**ft_path(char **ev);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_path(char **ev);
void		ffree(char **ptr);
int			ft_strchr(char *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		check_fail(int i, char *sp);

typedef struct t_da
{
	int		fdin;
	int		n;
	char	**av;
	int		fdout;
	char	**args;
	char	**path;
}			t_data;

int			ft_fork(char **env, char *arg, t_data *data, int check);
char		*ft_cmd(t_data *data, char *cmd);
t_data		*pars_inp(char **av, int ac, char **env);
#endif
