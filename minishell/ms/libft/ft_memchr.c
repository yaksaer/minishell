/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:44:00 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:36:47 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *source, int symbol, size_t len)
{
	unsigned char	*src;
	size_t			i;

	src = (unsigned char *)source;
	i = 0;
	while (i < len)
	{
		if (src[i] == (unsigned char)symbol)
			return ((void *)&src[i]);
		i++;
	}
	return (NULL);
}
