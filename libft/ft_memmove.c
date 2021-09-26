/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 00:27:12 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 14:56:54 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = -1;
	if ((unsigned char *)dest == NULL
		&& (unsigned char *)src == NULL)
		return (dest);
	if (dest <= src)
	{
		while (++i < n)
			((unsigned char *)dest)[i]
				= ((unsigned char *)src)[i];
	}
	else
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1]
				= ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}
