#include "libft.h"

t_node	*ft_dlist_get_n(t_dlink_list *list, size_t index)
{
	t_node	*tmp;
	size_t	i;

	tmp = NULL;
	if (index < list->size / 2)
	{
		i = 0;
		tmp = list->head;
		while (tmp && i < index)
		{
			tmp = tmp->next;
			i++;
		}
	}
	else
	{
		i = list->size - 1;
		tmp = list->tail;
		while (tmp && i > index)
		{
			tmp = tmp->prev;
			i--;
		}
	}
	return (tmp);
}
