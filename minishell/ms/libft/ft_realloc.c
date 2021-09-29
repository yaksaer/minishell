/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:08:50 by marvin            #+#    #+#             */
/*   Updated: 2021/09/28 19:57:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*result;
	size_t	ptr_size;

	if (!ptr)
		return(malloc(size));
	ptr_size = sizeof(ptr);
	if (size <= ptr_size)
		return (ptr);
	result = (void *)malloc(size);
	if (!result)
		return (NULL);
	result = ft_memset(result, 0, size);
	result = ft_memcpy(result, ptr, ptr_size);
	free(ptr);
	return (result);
}
