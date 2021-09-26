/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:32:22 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 15:06:31 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*d;
	char	sim;
	int		i;

	d = (char *)s;
	sim = (char)c;
	i = 0;
	while (d[i] && !(d[i] == sim))
		i++;
	if (d[i] == sim)
		return (d + i);
	return (NULL);
}
