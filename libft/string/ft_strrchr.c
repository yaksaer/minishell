/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:00:27 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/21 20:49:55 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	size_t		i;

	i = 1;
	while (string[i - 1] != '\0')
		i++;
	while (i >= 1)
	{
		if (string[i - 1] == symbol)
			return ((char *)&string[i - 1]);
		i--;
	}
	return (NULL);
}
