/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:00:51 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:39:06 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *string, size_t size)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)string;
	i = 0;
	while (i < size)
	{
		if (s[i] != '\0')
			s[i] = '\0';
		i++;
	}
}
