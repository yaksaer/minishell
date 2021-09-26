/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:02:34 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 15:08:12 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str1 && str1[i])
		i++;
	while (str2 && str2[j])
		j++;
	res = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str1 && str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	while (str2 && str2[j])
		res[i++] = str2[j++];
	res[i] = '\0';
	free(str1);
	return (res);
}
