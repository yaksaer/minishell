/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:41:32 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:33:27 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t len)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	if (!destination && !source)
		return (0);
	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	i = 0;
	if (src > dst)
	{
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i-- > 0)
			dst[i] = src[i];
	}
	return (dst);
}
