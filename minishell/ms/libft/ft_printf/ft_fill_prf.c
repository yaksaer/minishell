/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_prf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:16:04 by cbilbo            #+#    #+#             */
/*   Updated: 2021/02/27 21:03:41 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	fill_prf(t_printf *prf)
{
	prf->minus = 0;
	prf->zero = 0;
	prf->width = 0;
	prf->accuracy = -1;
	prf->base = 10;
	prf->upper = 'a';
	prf->type = -1;
	prf->length++;
}

void	flag_prf(t_printf *prf)
{
	while (prf->str[prf->length] == '-' || prf->str[prf->length] == '0')
	{
		if (prf->str[prf->length] == '-')
			prf->minus = 1;
		else
			prf->zero = 1;
		prf->length++;
	}
}

void	width_prf(t_printf *prf)
{
	if (prf->str[prf->length] == '*')
	{
		prf->width = va_arg(prf->arg, int);
		prf->length++;
		if (prf->width < 0)
		{
			prf->width = -prf->width;
			prf->minus = 1;
		}
		return ;
	}
	while (prf->str[prf->length] != '.' && ft_isdigit(prf->str[prf->length]) \
			&& (!(ft_strchr("cspdiuoxX%", prf->str[prf->length]))))
		prf->width = prf->width * 10 + (prf->str[prf->length++] - '0');
}

void	accuracy_prf(t_printf *prf)
{
	int		a;

	a = 0;
	if (prf->str[prf->length] != '.')
		return ;
	prf->length++;
	if (prf->str[prf->length] == '*')
	{
		prf->accuracy = va_arg(prf->arg, int);
		prf->length++;
		return ;
	}
	if (prf->str[prf->length] == '0')
		prf->accuracy = 0;
	while ((!(ft_strchr("cspdiuoxX%", prf->str[prf->length]))) \
		&& ft_isdigit(prf->str[prf->length]))
		a = a * 10 + (prf->str[prf->length++] - '0');
	prf->accuracy = a;
}

void	type_prf(t_printf *prf)
{
	char	s[2];

	s[0] = prf->str[prf->length];
	s[1] = '\0';
	if (ft_strchr("cspdiuoxX%", prf->str[prf->length]))
		prf->type = ft_strlen_until("cspdiuoxX%", s);
	else
		prf->type = 10;
	if (prf->type == LX || prf->type == UX || prf->type == P || prf->type == O)
	{
		if (prf->type == O)
			prf->base = 8;
		else
			prf->base = 16;
		if (prf->type == UX)
			prf->upper = 'A';
	}
}
