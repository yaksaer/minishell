/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 03:20:18 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 14:50:48 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*b;
	unsigned int	i;

	b = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		b[i] = 0;
		i++;
	}
	return (b);
}
