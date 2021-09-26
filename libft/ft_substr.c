/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:12:46 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 15:12:04 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub = (char *)malloc(1);
		return (sub);
	}
	while (s[start + j] && j < len)
		j++;
	sub = (char *)malloc(j + 1 * sizeof(char));
	if (sub == NULL)
		return (NULL);
	j = 0;
	while (j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
