#include "libft.h"

void	*ft_dlist_pop_front(t_dlink_list *list)
{
	t_node	*prev;
	void	*tmp;

	if (list->head == NULL)
		return (NULL);
	prev = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;
	if (prev == list->tail)
		list->tail = NULL;
	tmp = prev->data;
	free(prev);
	list->size--;
	return (tmp);
}
