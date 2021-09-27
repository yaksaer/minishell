/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:46:23 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:08:00 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*result;
	size_t	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (string[i] != '\0')
	{
		result[i] = string[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
