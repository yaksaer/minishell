/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:48:42 by marvin            #+#    #+#             */
/*   Updated: 2021/10/19 16:54:46 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoinm(char *string1, char *string2, int f)
{
	char	*result;
	int		i;
	int		j;
	int		len;

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
	}
	if (f == 1 || f == 3)
		ft_allocfree((void *)&string1);
	if (f == 2 || f == 3)
		ft_allocfree((void *)&string2);
	return (result);
}
