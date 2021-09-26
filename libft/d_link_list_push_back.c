#include "libft.h"

void	ft_dlist_push_back(t_dlink_list *list, int data)
{
	t_node	*tmp;

	tmp = (t_node *)malloc(sizeof(t_node));
	if (tmp == NULL)
		return ;
	tmp->data = data;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail)
		list->tail->next = tmp;
	list->tail = tmp;
	if (list->head == NULL)
		list->head = tmp;
	list->size++;
}
