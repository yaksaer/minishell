/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:59:15 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:06:24 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	char		*found;

	i = 0;
	found = (char *)haystack;
	if (ft_strlen(needle) == 0)
		return (found);
	while (haystack[i] && (i < len))
	{
		j = 0;
		while ((needle[j] == haystack[i + j]) && ((i + j) < len))
		{
			if (!(needle[j + 1]))
				return (found + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
