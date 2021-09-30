/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:08:50 by marvin            #+#    #+#             */
/*   Updated: 2021/09/30 18:49:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	void	*result;

	result = (void *)malloc(newsize);
	if (!result)
		return (NULL);
	ft_memset(result, 0, newsize);
	if (!ptr)
		return (result);
	result = ft_memcpy(result, ptr, oldsize);
	free(ptr);
	return (result);
}
