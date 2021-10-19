/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:58:22 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 10:53:51 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_env(t_main *main, char *str, int len)
{
	t_node	*env;
	char	*res;

	env = main->sort_env->head;
	while (env != NULL && (ft_strlen_until(env->data, "=") != len \
		|| ft_strncmp(str, env->data, len)))
		env = env->next;
	if (!env)
		return (NULL);
	res = ft_substr(env->data, len + 1, ft_strlen(env->data));
	return (res);
}

char	*put_env(t_main *main, char **string)
{
	char	*res;
	char	*str;
	int		len;
	int		i;

	res = NULL;
	str = *string;
	str++;
	len = ft_strlen_until(str, "\"\'?$<> |");
	if (!len && !ft_strchr("\'\"?$<> |", *str))
		len = ft_strlen(str);
	i = 0;
	res = find_env(main, str, len);
	str += len;
	*string = str;
	if (*str == '$' && ++*string)
		res = ft_strdup("80085");
	else if (*str == '?' && ++*string)
		res = ft_itoa(main->exit_code);
	if (*str == '?')
		main->exit_code = 0;
	return (res);
}

char	*parse_quotation(t_main *main, char **string, char quote)
{
	char	*str;
	char	*res;

	str = *string;
	str++;
	res = NULL;
	while (*str != quote)
	{
		if (!ft_strchr(str, quote))
			re_parser(main, quote);
		if (quote == '\"' && *str == '\\')
			re_parser(main, '\\');
		if (quote == '\"' && *str == '$' && str[1] \
			&& !ft_strchr(" \t|", str[1]))
			res = ft_strjoinm(res, put_env(main, &str), 3);
		else
			res = ft_add_char(res, *str++);
	}
	str++;
	*string = str;
	return (res);
}
