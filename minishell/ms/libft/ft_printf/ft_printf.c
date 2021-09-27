/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:21:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/12 17:54:15 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	fill_output_func(t_printf *prf)
{
	prf->output[C] = &output_c;
	prf->output[S] = &output_s;
	prf->output[P] = &output_nbr;
	prf->output[D] = &output_nbr;
	prf->output[I] = &output_nbr;
	prf->output[U] = &output_nbr;
	prf->output[O] = &output_nbr;
	prf->output[LX] = &output_nbr;
	prf->output[UX] = &output_nbr;
	prf->output[PERC] = &output_c;
	prf->output[10] = &output_c;
}

void	start_prf(char *string, t_printf *prf)
{
	prf->str = (char *)string;
	prf->str_len = ft_strlen(string);
	prf->num = 0;
	prf->length = 0;
	fill_output_func(prf);
}

void	ft_pars_prf(t_printf *prf)
{
	fill_prf(prf);
	flag_prf(prf);
	width_prf(prf);
	accuracy_prf(prf);
	type_prf(prf);
	prf->output[prf->type](prf);
	prf->length++;
}

void	printall(t_printf *prf)
{
	while (prf->length < prf->str_len)
	{
		if (prf->str[prf->length] == '%')
			ft_pars_prf(prf);
		else
			prf->num += write(1, &prf->str[prf->length++], 1);
	}
}

int	ft_printf(const char *string, ...)
{
	t_printf	prf;

	start_prf((char *)string, &prf);
	va_start(prf.arg, string);
	printall(&prf);
	va_end(prf.arg);
	return (prf.num);
}
