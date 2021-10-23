/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:11:24 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/22 16:20:24 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *string, int symbol)
{
	size_t		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (unsigned char)symbol)
			return ((char *)&string[i]);
		i++;
	}
	if (string[i] == (unsigned char)symbol)
		return ((char *)&string[i]);
	return (NULL);
}
