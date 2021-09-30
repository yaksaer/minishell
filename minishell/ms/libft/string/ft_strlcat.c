/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:00:40 by cbilbo            #+#    #+#             */
/*   Updated: 2020/11/27 16:30:27 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *destination, const char *source, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (destination[i] && i < len)
		i++;
	while (source[j] && ((i + j) + 1) < len)
	{
		destination[i + j] = source[j];
		j++;
	}
	if (i < len)
		destination[i + j] = '\0';
	return (i + ft_strlen(source));
}
