/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_link_list_pop_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:53:13 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:12:34 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_dlist_pop_back(t_dlink_list *list)
{
	t_node	*next;
	void	*tmp;

	if (list->tail == NULL)
		return (NULL);
	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;
	if (next == list->head)
		list->head = NULL;
	tmp = next->data;
	free(next);
	list->size--;
	return (tmp);
}
