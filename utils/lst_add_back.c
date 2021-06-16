#include "utils.h"

t_list	*lst_add_back(t_list **lst, char *line)
{
	t_list	*tail;
	t_list	*new;

	if (!line)
		return (0);
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (0);
	new->content = line;
	new->next = NULL;
	if (!(*lst))
		*lst = new;
	else
	{
		tail = ft_lstlast(*lst);
		tail->next = new;
	}
	return (new);
}

int		lst_clear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		free(tmp->content);
		*lst = (*lst)->next;
		free(tmp);
	}
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
