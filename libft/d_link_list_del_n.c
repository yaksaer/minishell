#include "libft.h"

void	*ft_dlist_del_n(t_dlink_list *list, size_t index)
{
	t_node	*elm;
	char	*tmp;

	elm = ft_dlist_get_n(list, index);
	if (elm == NULL)
		return (NULL);
	if (elm->prev)
		elm->prev->next = elm->next;
	if (elm->next)
		elm->next->prev = elm->prev;
	tmp = elm->data;
	if (!elm->prev)
		list->head = elm->next;
	if (!elm->next)
		list->tail = elm->prev;
	free(elm);
	list->size--;
	return (tmp);
}
