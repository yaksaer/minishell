/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:52:24 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:11:49 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstcpy(t_list *src)
{
	t_list	*res;

	if (!src)
		return (NULL);
	while (src)
	{
		ft_lstadd_back(&res, ft_lstnew(src->content));
		src = src->next;
	}
	return (res);
}
