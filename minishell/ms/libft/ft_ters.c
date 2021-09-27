/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:25:07 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 20:05:44 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ter_i(int arg, int first_res, int second_res)
{
	if (arg)
		return (first_res);
	return (second_res);
}

char	*ft_ter_s(int arg, char *first_res, char *second_res)
{
	if (arg)
		return (first_res);
	return (second_res);
}

double	ft_ter_d(int arg, double first_res, double second_res)
{
	if (arg)
		return (first_res);
	return (second_res);
}
