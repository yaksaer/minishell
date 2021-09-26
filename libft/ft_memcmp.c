/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:13:47 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 14:54:00 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;
	unsigned int	i;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (d1[i] != d2[i])
		{
			if (d1[i] > d2[i])
				return (d1[i] - d2[i]);
			return (d1[i] - d2[i]);
		}
		i++;
	}
	return (0);
}
