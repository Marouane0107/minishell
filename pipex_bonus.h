/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:06:20 by otamrani          #+#    #+#             */
/*   Updated: 2023/05/10 20:18:43 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
#  include <fcntl.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>
#  include <sys/errno.h>
#  include <sys/wait.h>
#  include <unistd.h>

size_t		ft_strlen(const char *s);
char		**ft_path(char **ev);
int			ft_strchr(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		stock(char *av, int fdin);
void		putstr_fd(char *s, int fd, char *m);
char		*get_next_line(int fd);
char		*ft_get_line(char *s);
void		check_fail(int i);
void		msg_error(char *sp);
int			ft_strcmp(char *s1, char *s2);
int			ft_strchr(char *s, char c);
void		ffree(char **ptr);

typedef struct s_data
{
	int		n;
	int		fdin;
	int		fdout;
	char	**args;
	char	**env;
	char	**path;
	char	**av;
}			t_data;
void		heredoc(char **av, int ac, t_data *data);
t_data		*pars_inp(char **av, int ac, char **env);
char		*ft_cmd(t_data *data, char *cmd);
# endif
#endif