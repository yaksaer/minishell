/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:38:43 by cbilbo            #+#    #+#             */
/*   Updated: 2021/02/20 00:53:07 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_until(const char *string, const char *smls)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (smls[i])
	{
		len = 0;
		while (string[len] != '\0' && string[len] != smls[i])
			len++;
		if (string[len] == smls[i])
			return (len);
		i++;
	}
	return (0);
}
