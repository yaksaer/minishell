#include "libft.h"

void	ft_dlist_push_front(t_dlink_list *list, int data)
{
	t_node	*tmp;

	tmp = (t_node *)malloc(sizeof(t_node));
	if (tmp == NULL)
		return ;
	tmp->data = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
		list->head->prev = tmp;
	list->head = tmp;
	if (list->tail == NULL)
		list->tail = tmp;
	list->size++;
}
