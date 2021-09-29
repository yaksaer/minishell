/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_link_list_push_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:53:03 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:12:49 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dlist_push_front(t_dlink_list *list, char *data)
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
