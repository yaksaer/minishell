/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_link_list_del_n.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:53:28 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:12:21 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
