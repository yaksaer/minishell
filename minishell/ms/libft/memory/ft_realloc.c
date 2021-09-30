/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:08:50 by marvin            #+#    #+#             */
/*   Updated: 2021/09/30 15:54:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*result;

	result = (void *)malloc(size);
	if (!result)
		return (NULL);
	ft_memset(result, 0, size);
	if (!ptr)
		return (result);
	ft_memccpy(result, ptr, 0, size);
	free(ptr);
	return (result);
}
