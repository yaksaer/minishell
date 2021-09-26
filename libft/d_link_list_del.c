#include "libft.h"

void	ft_dlist_del(t_dlink_list **list)
{
	t_node	*tmp;
	t_node	*next;

	tmp = (*list)->head;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}
