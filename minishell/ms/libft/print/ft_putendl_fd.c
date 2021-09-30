/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:22:22 by cbilbo            #+#    #+#             */
/*   Updated: 2020/11/27 16:11:29 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putendl_fd(char *string, int fd)
{
	size_t	i;

	if (!string)
		return ;
	i = ft_strlen(string);
	write(fd, string, i);
	write(fd, "\n", 1);
}
