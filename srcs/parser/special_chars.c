/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:58:22 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/22 19:36:56 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_var(t_main *main)
{
	int		len;
	char	*res;

	len = ft_strlen_until(main->var, " \t");
	if (len == 0)
	{
		res = ft_strdup(main->var);
		ft_allocfree((void *)&main->var);
		return (res);
	}
	res = ft_substr(main->var, 0, len);
	main->var = ft_strrepl(main->var, ft_strdup(main->var \
		+ len + ft_strlen_while(main->var + len, " \t")));
	return (res);
}

static int	parse_env(char **string, char **result)
{
	char	*str;
	char	*res;

	res = NULL;
	str = *string;
	if (ft_isdigit(str[1]) || ft_strchr("$?", str[1]))
	{
		if (str[1] == '?')
			res = ft_itoa(g_main->exit_code);
		else if (str[1] == '$')
			res = ft_strdup("80085");
		str += 2;
		*string = str;
		*result = res;
		return (1);
	}
	if (!ft_isalpha(str[1]) && str[1] != '_')
	{
		res = ft_add_char(res, *str++);
		res = ft_strjoinm(res, parse_word(g_main, &str), 3);
		*result = res;
		*string = str;
		return (1);
	}
	return (0);
}

char	*put_env(t_main *main, char **string)
{
	char	*res;
	char	*str;
	char	*key;
	int		len;
	t_node	*tmp;

	res = NULL;
	if (!ft_strchr("\'\"<> |/", **string) && parse_env(&*string, &res))
		return (res);
	str = *string;
	str++;
	len = ft_strlen_until(str, "$\"\'<>= |/");
	if (!len && !ft_strchr("$\'\"<> |/=", *str))
		len = ft_strlen(str);
	key = ft_substr(str, 0, len);
	tmp = find_key_node(main->sort_env, key);
	if (tmp && ft_strchr(tmp->data, '=') \
		&& ((ft_strchr(tmp->data, '=') + 1)[0] != '\0'))
		res = ft_strdup(ft_strchr(tmp->data, '=') + 1);
	str += len;
	*string = str;
	ft_allocfree((void *)&key);
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
