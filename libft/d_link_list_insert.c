#include "libft.h"

void	ft_dlist_insert(t_dlink_list *list, size_t index, int data)
{
	t_node	*elm;
	t_node	*ins;

	elm = NULL;
	ins = NULL;
	elm = ft_dlist_get_n(list, index);
	if (elm == NULL)
		return ;
	ins = (t_node *)malloc(sizeof(t_node));
	if (ins == NULL)
		return ;
	ins->data = data;
	ins->prev = elm;
	ins->next = elm->next;
	if (elm->next)
		elm->next->prev = ins;
	elm->next = ins;
	if (!elm->prev)
		list->head = elm;
	if (!elm->next)
		list->tail = elm;
	list->size++;
}
