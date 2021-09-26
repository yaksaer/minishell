/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:19:14 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 15:51:52 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countword(const char *s, char c)
{
	size_t	m;
	size_t	w;

	m = 0;
	w = 0;
	while (s[m])
	{
		while (s[m] == c && s[m])
			m++;
		if (s[m] != c && s[m])
			w++;
		while (s[m] != c && s[m])
			m++;
	}
	return (w);
}

static size_t	cntsim(const char *s, char c)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static char	**make_free(char **buf, size_t j)
{
	while (j)
	{
		free(buf[j]);
		j--;
	}
	free(buf);
	return (NULL);
}

static int	skip_c(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (countword(s, c) + 1));
	if (!res)
		return (NULL);
	while (j < countword(s, c))
	{
		i = skip_c(s, c);
		k = 0;
		res[j] = (char *)malloc(sizeof(char) * (cntsim(&s[i], c) + 1));
		if (!res)
			return (make_free(res, j));
		while (s[i] != c && s[i])
			res[j][k++] = s[i++];
		res[j++][k] = '\0';
	}
	res[j] = 0;
	return (res);
}
