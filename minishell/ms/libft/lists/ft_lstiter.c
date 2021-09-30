/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:44:34 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:11:57 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
