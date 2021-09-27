/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:09:28 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/17 18:50:52 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_of_int(long long int number)
{
	int	len;

	len = 0;
	if (number < 0)
	{
		number *= -1;
		len++;
	}
	if (number == 0)
		return (1);
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

char	*fill_the_string(long long int number, int len, \
								char *string, int minus)
{
	int	i;
	int	j;

	j = 1;
	i = len - 1;
	while (ft_ter_i(minus == 1, i > 0, i >= 0))
	{
		string[i--] = (number % 10) + 48;
		number /= 10;
		j++;
	}
	if (minus == 1)
	{
		string[0] = '-';
		string[j] = '\0';
	}
	else
		string[j - 1] = '\0';
	return (string);
}

char	*ft_itoa(int number)
{
	long long int	num;
	size_t			len;
	size_t			minus;
	char			*string;

	minus = 0;
	num = number;
	len = len_of_int(num);
	string = (char *)malloc((len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	if (num < 0)
	{
		num *= -1;
		minus = 1;
	}
	fill_the_string(num, len, string, minus);
	return (string);
}
