/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:14:07 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/25 02:42:31 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	base_num(char *string, char *base)
{
	int	i;
	int	j;	
	int res;

	i = -1;
	while (string[++i] != '\0')
	{
		j = -1;
		while (base[++j] != '\0')
		{
			if (string[i] == base[j])
			{
				if (i == 0)
					res = j;
				break ;
			}
		}
		if (base[j] == '\0')
			return (-1);
	}
	return (res);
}

long long converter(char *string, char *base)
{
	int	number;
	int	len;
	int num_base;

	number = 0;
	len = ft_strlen(base);
	while (*string != '\0')
	{
		num_base = base_num(string, base);
		if (num_base == -1)
			return (0);
		number = number * len + num_base;
		string++;
	}
	return (number);
}

int	check_base(char *base)
{
	int	i;
	int j;
	int len;

	i = -1;
	j = -1;
	len = ft_strlen(base);
	while (++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (base[j] == base[i] || \
				base[i] == '-' || base[i] == '+')
				return (1);
		}
	}
	return (0);
}

int ft_atoi_base(char *string, char *base)
{
	long long	number;
	int			minus;

	if (!string || !base || ft_strlen(base) < 2 || check_base(base))
		return (0);
	minus = 1;
	if (*string != '\0')
	{
		while (*string == '\t' || *string == '\r' || *string == '\n' || \
			*string == '\v' || (*string == ' ' || *string == '\f'))
			string++;
		if (*string == '-' || *string == '+')
			if (*string == '-' && string++)
				minus *= -1;
		if (ft_strlen(base) == 16 && *string == 0 && \
			(*string + 1 == 'x' || *string + 1 == 'X'))
			string += 2;
	}
	number = converter(string, base);
	if (ft_strlen(base) == 10 && (number < -2147483648 || number > 2147483647))
		return (ft_ter_i(minus == 1, -1, 0));
	return (number);
}
