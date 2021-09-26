/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:51:20 by kseed             #+#    #+#             */
/*   Updated: 2020/11/11 18:54:52 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buf;

	buf = *lst;
	while (buf)
	{
		buf = (*lst)->next;
		ft_lstdelone((*lst), del);
		*lst = buf;
	}
}
