#include "minishell.h"
void	ft_free(char **p)
{
	int		i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}
t_list	*ft_lstnew(char *s,int content)
{
	t_list	*node;

	node = NULL;
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	if (node)
	{
		node->token = content;
        node->content = s;
		node->next = NULL;
	}
	return (node);
}

t_data	*ft_lstnew2(char **s,int in, int out)
{
	t_data	*node;

	node = NULL;
	node = malloc(sizeof(t_data));
	if (!node)
		return (0);
	if (node)
	{
		node->out = out;
		node->in = in;
        node->cmd = s;
		node->next = NULL;
	}
	return (node);
}
void	ft_lstadd_back2(t_data **lst, t_data *new)
{
	t_data	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}
void	ft_lstadd_front(t_list **st_a, t_list *new)
{
	t_list	*tmp;

	tmp = NULL;
	if (new)
	{
		tmp = *st_a;
		while (tmp)
		{
			if (tmp->next == new)
			{
				tmp->next = tmp->next->next;
				break ;
			}
			tmp = tmp->next;
		}
		new->next = *st_a;
		*st_a = new;
	}
}
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst)->content)
	{
		(*lst)->content = new->content;
		(*lst)->token = new->token;
		(*lst)->next = new->next;
	}
	else
	{
		tmp = *lst;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		new->envi = tmp->envi;
		tmp->next = new;
	}
}

int	ft_lstsize(t_data *lst)
{
	t_data	*tmp;
	int			i;

	i = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}