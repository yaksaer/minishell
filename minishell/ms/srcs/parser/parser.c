/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/09/29 17:07:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_realloc(void *ptr, size_t num, size_t size)
{
	void	*result;

	if (!ptr)
	{
		result = ft_calloc(num, size);
		return (result);
	}
	result = ft_calloc(num, size);
	if (!result)
		return (NULL);
	result = ft_memcpy(result, ptr, num);
	free(ptr);
	return (result);
}

char	*handle_quotation(char *str, char c)
{
	static int	single = 0;
	static int	doubl = 0;
	char		*res;

	res = NULL;
	if (ft_strchr("\'\"", c) && !single && !doubl)
	{
		single = ft_ter_i(c == '\'', 1, single);
		doubl = ft_ter_i(c == '\"', 1, doubl);
		return (str);
	}
	if ((c == '\'' && doubl) || (c == '\"' && single))
	{
		res = (char *)ft_realloc((char *)res, ft_strlen(res) + 2, sizeof(char));
		res[ft_strlen(res)] = c;
	}
	return (res);	
}

void	handle_string(t_main *main, char *str)
{
	char	*res;
	int		i;

	res = NULL;
	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_strchr("\'\"", str[i]))
			res = handle_quotation(res, str[i]);
		else
		{
			res = (char *)ft_realloc(res, ft_strlen(res) + 2, sizeof(char));
			res[ft_strlen(res)] = str[i];
		}
	}
	printf("%s\n", res);
	ft_allocfree((void *)&res);
}

int	parser(t_main *main)
{
	char	*str;

	str = readline(BEGIN(49, 32)"Minishell: "CLOSE);
	if (str[0] == 'q')
	{
		free(str);
		return (1);
	}
	printf("%s\n", str);
	handle_string(main, str);
	ft_allocfree((void *)&str);
	return (0);
}