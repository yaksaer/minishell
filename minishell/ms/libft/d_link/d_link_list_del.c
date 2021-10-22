/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_link_list_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:53:24 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:12:24 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dlist_del(t_dlink_list **list)
{
	t_node	*tmp;
	t_node	*next;

	tmp = (*list)->head;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->data);
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}
