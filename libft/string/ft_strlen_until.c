/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:38:43 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/14 21:17:46 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_until(const char *string, const char *smls)
{
	int		len;
	int		i;
	int		j;

	i = -1;
	len = -1;
	while (smls[++i])
	{
		j = -1;
		while (string[++j])
		{
			if (string[j] == smls[i] && (j < len || len == -1))
			{
				len = j;
				break ;
			}
		}
	}
	return (ft_ter_i(len == -1, 0, len));
}
