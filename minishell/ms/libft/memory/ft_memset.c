/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 19:25:39 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:11:46 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *destination, int symbol, size_t len)
{
	unsigned char	*dst;
	size_t			i;

	dst = (unsigned char *)destination;
	i = 0;
	while (i < len)
	{
		dst[i] = (unsigned char)symbol;
		i++;
	}
	return (dst);
}
