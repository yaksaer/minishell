/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:18:13 by cbilbo            #+#    #+#             */
/*   Updated: 2020/11/27 16:12:50 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_fd(char const *string, int fd)
{
	size_t		i;

	if (string)
	{
		i = 0;
		while (string[i] != '\0')
			i++;
		write(fd, string, i);
	}
}
