/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:38:43 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/07 11:47:43 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_until(const char *string, const char *smls)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = -1;
	while (smls[++i])
	{
		j = -1;
		len = 0;
		while (string[++j])
		{
			if (string[j] == smls[i] && (j < len || len == 0))
				len = j;
		}
		return (len);
	}
	return (0);
}
