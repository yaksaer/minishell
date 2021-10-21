/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:56 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/20 15:30:10 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strstr_count(char *dest, char *needle)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (dest[i])
	{
		j = 0;
		while (needle[j] == dest[i + j])
		{
			if (!(needle[j + 1]))
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (count);
}
