/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:53:34 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:53:36 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *string1, char const *string2)
{
	char		*result;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	j = 0;
	len = ft_strlen(string1) + ft_strlen(string2);
	result = ft_calloc(len + 1, sizeof(char));
	if (result != NULL)
	{
		while (string1 && string1[i] != '\0')
		{
			result[i] = string1[i];
			i++;
		}
		while (string2 && string2[j] != '\0')
			result[i++] = string2[j++];
		result[i] = '\0';
	}
	return (result);
}
