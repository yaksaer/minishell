/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:35:39 by cbilbo            #+#    #+#             */
/*   Updated: 2021/02/27 21:03:36 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	printadress(t_printf *prf)
{
	if (prf->type == P)
		prf->num += write(1, "0x", 2);
}

void	nbr_with_accu(long nbr, t_printf *prf, int len)
{
	if (len <= prf->accuracy && nbr < 0)
	{
		prf->accuracy++;
		if (prf->width < prf->accuracy)
			prf->width++;
	}
	if (prf->accuracy < len)
		prf->accuracy = len;
	if (prf->width < prf->accuracy)
		prf->width = prf->accuracy;
	if (prf->minus)
	{
		ft_nbrminus_prf(&nbr, prf);
		prf->num += ft_putcharl('0', prf->accuracy - len);
		printadress(prf);
		ft_putnbr_base_prf(nbr, prf);
		prf->num += ft_putcharl(' ', prf->width - prf->accuracy);
		return ;
	}
	prf->num += ft_putcharl(' ', prf->width - prf->accuracy);
	ft_nbrminus_prf(&nbr, prf);
	printadress(prf);
	prf->num += ft_putcharl('0', prf->accuracy - len);
	ft_putnbr_base_prf(nbr, prf);
}

void	nbr_without_accu(long nbr, t_printf *prf, int len)
{
	char	space;

	space = ' ';
	if (prf->zero && !prf->minus)
	{
		space = '0';
		ft_nbrminus_prf(&nbr, prf);
	}
	if (len < prf->width)
		prf->accuracy = prf->width - len;
	else
		prf->accuracy = 0;
	if (prf->minus)
	{
		printadress(prf);
		ft_putnbr_base_prf(nbr, prf);
		prf->num += ft_putcharl(space, prf->accuracy);
		return ;
	}
	prf->num += ft_putcharl(space, prf->accuracy);
	ft_nbrminus_prf(&nbr, prf);
	printadress(prf);
	ft_putnbr_base_prf(nbr, prf);
}

void	nbr_is_null(t_printf *prf)
{
	if (prf->type == P && prf->minus)
		printadress(prf);
	prf->num += ft_putcharl(' ', prf->width);
	if (prf->type == P && !prf->minus)
		printadress(prf);
}

void	output_nbr(t_printf *prf)
{
	long	nbr;
	int		len;

	len = 0;
	if (prf->type == P)
	{
		nbr = va_arg(prf->arg, unsigned long);
		prf->width -= 2;
	}
	else if (prf->type == D || prf->type == I)
		nbr = va_arg(prf->arg, int);
	else
		nbr = va_arg(prf->arg, unsigned int);
	len = ft_nbrlen_prf(nbr, prf);
	if (prf->accuracy < 0)
		nbr_without_accu(nbr, prf, len);
	else
	{
		if (!nbr && prf->accuracy == 0)
			nbr_is_null(prf);
		else
			nbr_with_accu(nbr, prf, len);
	}
}
