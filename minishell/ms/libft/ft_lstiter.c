/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:44:34 by cbilbo            #+#    #+#             */
/*   Updated: 2020/11/27 16:33:10 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*function)(void *))
{
	t_list	*list;

	if (!lst)
		return ;
	list = lst;
	if (function)
	{
		while (list->next != NULL)
		{
			function(list->content);
			list = list->next;
		}
		function(list->content);
	}
}
