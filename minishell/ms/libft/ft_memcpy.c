/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:00:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:33:36 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t len)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	if (!source && !destination)
		return (NULL);
	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
