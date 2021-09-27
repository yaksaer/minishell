/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:25:34 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 18:09:37 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	words_count(char const *string, char symbol)
{
	size_t	i;
	size_t	count_of_words;

	i = 0;
	count_of_words = 0;
	while (string[i] != '\0')
	{
		if (string[i] != symbol && (string[i + 1] == symbol \
									|| string[i + 1] == '\0'))
			count_of_words++;
		i++;
	}
	return (count_of_words);
}

int	len_of_word(char const *string, char symbol)
{
	size_t	len;

	len = 0;
	while (string[len] != symbol && string[len] != '\0')
		len++;
	return (len);
}

void	*freewords(char **result, size_t count_of_words)
{
	size_t	i;

	i = 0;
	while (i < count_of_words)
		free(result[i++]);
	free(result);
	return (NULL);
}

char	**secateurs(char const *string, char symbol, \
					size_t count_of_words, char **result)
{
	int		i;
	size_t	j;
	size_t	len;

	i = -1;
	while (++i < (int)count_of_words)
	{
		j = 0;
		while (*string == symbol)
			string++;
		len = len_of_word(string, symbol);
		result[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!result[i])
			return (freewords(result, count_of_words));
		while (j < len)
			result[i][j++] = *string++;
		result[i][j] = '\0';
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *string, char symbol)
{
	size_t	count_of_words;
	char	**result;

	if (!string)
		return (NULL);
	count_of_words = words_count(string, symbol);
	result = (char **)malloc((count_of_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	*result = *secateurs(string, symbol, count_of_words, result);
	return (result);
}
