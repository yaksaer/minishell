/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:18:02 by cbilbo            #+#    #+#             */
/*   Updated: 2020/11/27 16:33:35 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*function)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*result;

	if (!lst || !function)
		return (NULL);
	new_list = ft_lstnew(function(lst->content));
	result = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew(function(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = NULL;
	return (result);
}
