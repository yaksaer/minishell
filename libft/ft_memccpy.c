/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 04:30:00 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 14:53:48 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	sim;
	unsigned int	i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	sim = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s[i] == sim)
		{
			d[i] = s[i];
			return (d + i + 1);
		}
		d[i] = s[i];
		i++;
	}
	return (NULL);
}
