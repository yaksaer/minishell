/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:20:11 by cbilbo            #+#    #+#             */
/*   Updated: 2020/11/27 16:31:14 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *destination, const char *source, size_t len)
{
	size_t	i;
	size_t	l;

	l = 0;
	i = 0;
	if (!source || !destination)
		return (0);
	while (source[l] != '\0')
		l++;
	if (len > 0)
	{
		while (i < len - 1 && source[i] != '\0')
		{
			destination[i] = source[i];
			i++;
		}
		destination[i] = '\0';
	}
	return (l);
}
