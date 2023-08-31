/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:28:50 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/01 00:54:18 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
#  define word 0
#  define PIPE 1
#  define redin 2
#  define redout 3
#  define append 4
#  define heredoc 5
#  define file -1
#  include "./libft/libft.h"
#  include <dirent.h>
#  include <errno.h>
#  include <fcntl.h>
#  include <readline/history.h>
#  include <readline/readline.h>
#  include <signal.h>
#  include <stdbool.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>
#  include <sys/errno.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#  include <sys/wait.h>
#  include <unistd.h>
int					quote(char *in);
void				parss(void);
void				ffree(char **p);
int					ft_strchrr(char *s, char c);

typedef struct s_list
{
	char			*content;
	int				token;
	int				num;
	struct s_list	*next;
}					t_list;
typedef struct s_env
{
	char			*value;
	char			*name;
	struct s_env	*next;
}					t_env;
typedef struct s_grbg
{
	char			*s;
	t_list			*lst;
	char 			*p;
	char 			**l;
	struct s_grbg	*next;
}					t_grbg;
typedef struct s_global
{
	int				g;
	t_env			*env;
	int				ex;
	t_grbg			*hold;
}					t_global;

extern t_global		g_lobal;


typedef struct s_data
{
	int				status;
	t_env			*env;
	char			**cmd;
	int				in;
	int				out;
	struct s_data	*next;

}					t_data;
t_data				*convert_lst(t_list *lst);
void 		msg_error(t_list *lst);
void				ft_lstadd(t_grbg **lst, t_grbg *new);
t_grbg 	*lst_new(char **p, char *name, char *value);
int					pparss(char *input);
void 	free_lst(t_list *lst);
char				*ft_get_line(char *s);
char				*ft_str(char s);
char				*get_next_line(int fd);
void				sigint_handler(int sig);
int	get_exp(char *s, int j, char *q, int m);
t_env				*get_environ(void);
char				*check_expend(char *s, t_list **lst, int j);
int					ft_lstsize(t_data *lst);
t_data				*ft_lstnew2(char **s, int in, int out);
void				ft_lstadd_back2(t_data **lst, t_data *new);
int					ft_word(char *s, t_list **lst);
int					fil_env(t_list **lst);
int					detach_separted(char *str, t_list **lst);
int					end_struct(t_list **lst);
int					ftlen(char *str);
int					ft_countd(char *str);
t_list				*ft_lstnew(char *s, int content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **st_a, t_list *new);
char	*searsh_env(char *c);
int					syntax_error(char *str);
int					check_spacial(char *str);
void				add_node(t_list **head, char *content, int token);
// typedef struct s_list
// {
// 	char			*content;
// 	int				token;
// 	int 			in;
// 	int 			out;
// 	struct s_list	*next;
// }t_list;

# endif
#endif