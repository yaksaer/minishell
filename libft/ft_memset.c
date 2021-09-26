/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:18:51 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 14:57:16 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*b;
	unsigned int	i;

	b = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		b[i] = c;
		i++;
	}
	return (b);
}
