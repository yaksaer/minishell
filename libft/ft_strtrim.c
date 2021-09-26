/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:57:40 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 15:11:00 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	i;
	char	*res;
	char	*st;
	char	*fi;

	i = 0;
	if (!s)
		return (NULL);
	while (*s && ft_strchr(set, *s))
		s++;
	st = (char *)s;
	while (*s)
		s++;
	s--;
	while (s > st && ft_strchr(set, *s))
		s--;
	fi = (char *)s;
	res = (char *)malloc((fi - st + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (st <= fi)
		res[i++] = *st++;
	res[i] = '\0';
	return (res);
}
