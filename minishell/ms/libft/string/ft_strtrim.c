/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:50:23 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:06:00 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	first_symbol(char const *string, char const *excess)
{
	size_t		fs;
	size_t		j;

	fs = 0;
	j = 0;
	while (string[fs] != '\0' && excess[j] != '\0')
	{
		if (string[fs] == excess[j])
		{
			fs++;
			j = 0;
		}
		else
			j++;
	}
	return (fs);
}

int	last_symbol(char const *string, char const *excess, size_t len)
{
	int		ls;
	int		j;

	ls = (int)len - 1;
	j = 0;
	while (ls >= 0 && excess[j] != '\0')
	{
		if (string[ls] == excess[j])
		{
			ls--;
			j = 0;
		}
		else
			j++;
	}
	return (ls);
}

char	*ft_strtrim(char const *string, char const *excess)
{
	char	*result;
	size_t	fs;
	int		ls;
	size_t	len;

	if (!string || !excess)
		return (0);
	len = ft_strlen(string);
	fs = first_symbol(string, excess);
	ls = last_symbol(string, excess, len);
	if (ls < (int)fs)
		len = 1;
	else
		len = (size_t)ls - fs + 1;
	result = ft_substr(string, fs, len);
	return (result);
}
