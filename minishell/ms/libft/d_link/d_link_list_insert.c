/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_link_list_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:53:16 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:12:31 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dlist_insert(t_dlink_list *list, size_t index, char *data)
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
	if (!ins->next)
		list->tail = ins;
	list->size++;
}
