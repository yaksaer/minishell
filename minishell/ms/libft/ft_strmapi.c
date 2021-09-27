/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:05:46 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:07:16 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *string, char (*function)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*result;

	i = 0;
	len = 0;
	if (!string || !function)
		return (NULL);
	while (string[len] != '\0')
		len++;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (string[i] != '\0')
	{
		result[i] = function(i, string[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
