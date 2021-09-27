/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:50:52 by cbilbo            #+#    #+#             */
/*   Updated: 2021/01/28 15:37:17 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int number, int base)
{
	unsigned char	symbol;

	if (number < 0)
	{
		write(1, "-", 1);
		ft_putnbr_base(-number, base);
	}
	if (number >= base)
	{
		ft_putnbr_base(number / base, base);
		symbol = number % base + '0';
		write(base, &symbol, 1);
	}
	else
	{
		symbol = number + '0';
		write(base, &symbol, 1);
	}
}
