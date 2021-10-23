/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:50:52 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/12 19:29:11 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_base_prf(long number, t_printf *prf)
{
	unsigned char	symbol;

	if (number == 0)
	{
		prf->num += write(1, "0", 1);
		return ;
	}
	if (number < 0)
	{
		prf->num += write(1, "-", 1);
		number = -number;
	}
	if (number >= prf->base)
	{
		ft_putnbr_base_prf(number / prf->base, prf);
		symbol = number % prf->base + (ft_ter_i(number % prf->base > 9, \
			prf->upper - 10, '0'));
		prf->num += write(1, &symbol, 1);
	}
	else
	{
		symbol = number + (ft_ter_i(number % prf->base > 9, \
			prf->upper - 10, '0'));
		prf->num += write(1, &symbol, 1);
	}
}

int	ft_nbrlen_prf(long nbr, t_printf *prf)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	if ((nbr / prf->base) != 0)
		len += ft_nbrlen_prf(nbr / prf->base, prf);
	len++;
	return (len);
}

void	ft_nbrminus_prf(long *nbr, t_printf *prf)
{
	if (*nbr < 0)
	{
		prf->num += write(1, "-", 1);
		*nbr = -*nbr;
	}
}
