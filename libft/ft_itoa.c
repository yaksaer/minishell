/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:01:54 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 14:53:02 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size(int numb)
{
	size_t	ln;

	ln = 0;
	if (numb == 0)
		return (1);
	while (numb)
	{
		numb /= 10;
		ln++;
	}
	return (ln);
}

char	*ft_itoa(int n)
{
	long int	nb;
	char		*s;
	size_t		len;

	nb = n;
	len = size(n);
	if (nb < 0)
		len += 1;
	if (nb < 0)
		nb *= -1;
	s = (char *)malloc((sizeof(char)) * len + 1);
	if (!s)
		return (NULL);
	*(s + len) = '\0';
	while (len--)
	{
		*(s + len) = nb % 10 + '0';
		nb /= 10;
	}
	if (s[0] == '0' && n != 0)
		s[0] = '-';
	return (s);
}
