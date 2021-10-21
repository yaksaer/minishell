/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:49:33 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/29 13:11:53 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdelone(t_list *lst, void *(*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		(del(lst->content));
	free(lst);
}
