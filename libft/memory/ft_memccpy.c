/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:27:14 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/30 15:26:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *destination, const void *source, \
							int lastchar, size_t count)
{
	unsigned char	*dst;
	unsigned char	*src;
	unsigned char	lach;
	size_t			i;

	if (source == NULL || !source)
		return (destination);
	if (!destination)
		return (NULL);
	lach = lastchar;
	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = -1;
	while (++i < count)
	{
		dst[i] = src[i];
		if (src[i] == lach)
			return ((void *)&dst[i]);
	}
	return (NULL);
}
