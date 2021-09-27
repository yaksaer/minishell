/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:27:14 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:37:01 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, \
							int lastchar, size_t count)
{
	unsigned char	*dst;
	unsigned char	*src;
	unsigned char	lach;
	size_t			i;

	lach = lastchar;
	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = 0;
	while (i < count)
	{
		dst[i] = src[i];
		if (src[i++] == lach)
			return ((void *)&dst[i]);
	}
	return (NULL);
}
