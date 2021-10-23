/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:00:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/30 14:58:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t len)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	if (!source && !destination)
		return (NULL);
	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = -1;
	while (++i < len)
	{
		dst[i] = src[i];
	}
	return (dst);
}
