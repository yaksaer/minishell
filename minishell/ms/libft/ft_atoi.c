/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:29:30 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/20 15:25:18 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *string)
{
	long long int	number;
	int				i;
	int				minus;

	i = 0;
	minus = 1;
	number = 0;
	if (string[i] != '\0')
	{
		while (string[i] == '\t' || string[i] == '\r' || string[i] == '\n' \
			|| string[i] == '\v' || string[i] == ' ' || string[i] == '\f')
			i++;
		if (string[i] == '-' || string[i] == '+')
		{
			if (string[i++] == '-')
				minus *= -1;
		}
		while (string[i] >= '0' && string[i] <= '9')
		{
			number = number * 10 + ((string[i++] - '0') * minus);
			if (number < -2147483648 || number > 2147483647)
				return (ft_ter_i(minus == 1, -1, 0));
		}
	}
	return (number);
}
