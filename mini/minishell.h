/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:28:50 by otamrani          #+#    #+#             */
/*   Updated: 2023/09/08 16:12:51 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define WORD 0
# define PIP 1
# define REDIN 2
# define REDOUT 3
# define APPEND 4
# define HERDOC 5
# define FIL -1
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 102400

int					quote(char *in);
void				parss(void);
void				ft_free(char **p);
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
	char			*p;
	char			**l;
	struct s_grbg	*next;
}					t_grbg;
typedef struct s_global
{
	int				n;
	int				g;
	int				i;
	int				j;
	t_env			*env;
	int				ex;
	t_grbg			*hold;
}					t_global;

extern t_global		g_lobal;

typedef struct s_data
{
	int				status;
	int				f;
	char			**cmd;
	int				in;
	int				out;
	struct s_data	*next;

}					t_data;
t_data				*convert_lst(t_list *lst);
int					openout(t_list *lst);
int					openin(t_list *tmp, char **s, int j);
char				*ft_getenv(char *s);
t_env				*ft_lstdadd_back1(t_env **lst, t_env *new);
t_grbg				*lst_new(char **p, char *name, char *value);
t_env				*ft_lstnew1(char *name, char *value);
void				ft_skip(t_list **lst);
char				*ft_str(char s);
void				add_node(t_list **head, char *content, int token);
void				remove_node(t_data *data, char *name);
void				ft_free_linkdlist(t_data *data, t_list *lst);
void				ft_unset(t_data *cmd);
void				ft_env(t_data *data);
void				ft_pwd(void);
void				ft_cd(t_data *data);
void				ft_exit(t_data *data);
void				ft_echo(t_data *data);
void				ft_export(t_data *data);
void				ft_lstadd_back2(t_data **lst, t_data *new);
void				ft_exec(t_data *data);
void				exec_cmd(t_data *data);
int					milti_pipe(t_data *tmp, int fd[2]);
void				out_in_file(t_data *data);
void				parent(int fd[2]);
void				child(t_data *data, int fd[2]);
void				ft_close_file(t_data *data);
void				ft_close_pipe(int fd[2]);
int					ft_setenv(t_data *data, char *s, char *value);
int					cmd_check(t_data *data);
char				*searsh_env(char *c, int j);
int					get_exp(char *s, int j, char *q, int m);
int					check_single(char *s, int j);
int					adge_case(char *s, int j, char *q);
char				**open_here(t_list *lst);
char				*stock(char *av, t_list *lst);
int					count_x(t_list *lst, int j);
void				fill(t_data **data, t_list *lst, char **s);
void				add_cmd(t_list *lst, t_data **tmp);
void				handle_tokens(t_list **lst, t_data **data, char **s, int j);
void				msg_error(t_list *lst);
int					ins(char c, int m, int j);
void				ft_lstadd(t_grbg **lst, t_grbg *new);
t_grbg				*lst_new(char **p, char *name, char *value);
t_data				*distribut(char *input);
void				free_lst(t_list *lst);
void				free_env(t_env *env);
void				free_data(t_data *data);
char				*ft_get_line(char *s);
char				*ft_str(char s);
char				*get_next_line(int fd);
void				sigint_handler(int sig);
int					get_exp(char *s, int j, char *q, int m);
t_env				*get_environ(void);
char				*check_expend(char *s, t_list **lst, int j);
t_data				*ft_lstnew2(int in, int out, int i);
void				ft_lstadd_back2(t_data **lst, t_data *new);
int					ft_word(char *s, t_list **lst);
int					detach_separted(char *str, t_list **lst);
int					end_struct(t_list **lst);
int					ftlen(char *str);
int					ft_countd(char *str);
t_list				*ft_lstnew(char *s, int content);
void				ft_lstadd_back(t_list **lst, t_list *new);
char				*searsh_env(char *c, int j);
int					syntax_error(char *str);
int					check_spacial(char *str);
void				add_node(t_list **head, char *content, int token);

#endif