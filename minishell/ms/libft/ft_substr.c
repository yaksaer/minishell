/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:52:05 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:05:41 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *string, unsigned int start, size_t len)
{
	char		*result;
	size_t		i;
	size_t		l;

	if (!string)
		return (0);
	i = 0;
	l = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < start)
		i++;
	while (l <= len - 1 && string[i] != '\0' && \
			start < ft_strlen(string) && len != 0)
		result[l++] = string[i++];
	result[l] = '\0';
	return (result);
}
