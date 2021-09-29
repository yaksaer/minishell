/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/09/29 14:15:39 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_quotetion(char *res, char c, int *single, int *doubl)
{
	if (ft_strchr("\'\"", c) && !*single && !*doubl)
	{
		*single = ft_ter_i(c == '\'', 1, *single);
		*doubl = ft_ter_i(c == '\"', 1, *doubl);
	}
	else if (ft_strchr("\'\"", c) && \
			((*single && !*doubl) || (*doubl && !*single)))
	{
		res = (char *)ft_realloc(res, ft_strlen(res) + 1);
		res[ft_strlen(res)] = c;
	}
	if (c == '\'')
		*single = 0;
	else if (c == '\"')
		*doubl = 0;
	return (res);
}

char	*preparsing(char *str)
{
	char	*res;
	int		single;
	int		doubl;

	single = 0;
	doubl = 0;
	res = NULL;
	while (*str != '\0' || *str != '|')
	{
		if (ft_strchr("\'\"", *str))
		{
			res = handle_quotetion(res, *str, &single, &doubl);
		}
		str++;
	}
	return (res);
}

void	handle_string(t_main *main, char *string)
{
	int		i;
	int		len;
	char	*str;

	i = -1;
	str = preparsing(string);
	printf("%s\n", str);
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