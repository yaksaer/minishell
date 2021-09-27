/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:26:51 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/12 19:27:16 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	s_with_acc(char *str, int len, t_printf *prf)
{
	char	space;

	space = (char)ft_ter_i(prf->zero == 1, '0', ' ');
	if (len < prf->accuracy)
		prf->accuracy = len;
	if (prf->width < prf->accuracy)
		prf->width = prf->accuracy;
	if (prf->minus == 1)
	{
		prf->num += ft_putstrl(str, prf->accuracy);
		prf->num += ft_putcharl(' ', prf->width - prf->accuracy);
	}
	else
	{
		prf->num += ft_putcharl(space, prf->width - prf->accuracy);
		prf->num += ft_putstrl(str, prf->accuracy);
	}
}

void	s_without_acc(char *str, int len, t_printf *prf)
{
	char	space;

	space = (char)ft_ter_i(prf->zero == 1, '0', ' ');
	if (len < prf->width)
		prf->accuracy = prf->width - len;
	else
		prf->accuracy = 0;
	if (prf->minus == 1)
	{
		prf->num += ft_putstrl(str, len);
		prf->num += ft_putcharl(' ', prf->accuracy);
	}
	else
	{
		prf->num += ft_putcharl(space, prf->accuracy);
		prf->num += ft_putstrl(str, len);
	}
}

void	output_s(t_printf *prf)
{
	char	*str;
	int		len;

	str = va_arg(prf->arg, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (prf->accuracy >= 0)
		s_with_acc(str, len, prf);
	else
		s_without_acc(str, len, prf);
}

void	output_c(t_printf *prf)
{
	int		c;
	char	space;

	space = (char)ft_ter_i(prf->zero && !prf->minus, '0', ' ');
	if (prf->type == 10)
		c = prf->str[prf->length];
	else
		c = (int)ft_ter_i(prf->type == PERC, '%', va_arg(prf->arg, int));
	if (prf->type == 10 && prf->length == prf->str_len)
		return ;
	if (prf->width > 0)
	{
		if (prf->minus == 1)
		{
			prf->num += write(1, &c, 1);
			prf->num += ft_putcharl(space, prf->width - 1);
		}
		else
		{
			prf->num += ft_putcharl(space, prf->width - 1);
			prf->num += write(1, &c, 1);
		}
	}
	else
		prf->num += write(1, &c, 1);
}
