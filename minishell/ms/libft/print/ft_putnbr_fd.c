/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:35:00 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/19 19:05:48 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int number, int fd)
{
	unsigned char	symbol;

	if (number == -2147483648)
		write(fd, "-2147483648", 11);
	else if (number < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-number, fd);
	}
	else if (number >= 10)
	{
		ft_putnbr_fd(number / 10, fd);
		symbol = number % 10 + '0';
		write(fd, &symbol, 1);
	}
	else
	{
		symbol = number + '0';
		write(fd, &symbol, 1);
	}
}
