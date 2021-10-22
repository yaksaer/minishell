/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:58:22 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/21 19:28:35 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_env(t_main *main, char *str, int len)
{
	t_node	*env;
	char	*res;

	env = main->sort_env->head;
	while (env != NULL && ((int)ft_strlen_until(env->data, "=") != len \
		|| ft_strncmp(str, env->data, len)))
		env = env->next;
	if (!env)
		return (NULL);
	res = ft_substr(env->data, len + 1, ft_strlen(env->data));
	return (res);
}

static int	parse_env(char **string, char **result)
{
	char	*str;
	char	*res;

	res = NULL;
	str = *string;
	if (ft_isdigit(str[1]))
	{
		str += 2;
		*string = str;
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
	int		len;

	res = NULL;
	str = *string;
	if (!ft_strchr("$?\'\"<> |/", *str) && parse_env(&str, &res))
	{
		*string = str;
		return (res);
	}
	str++;
	len = ft_strlen_until(str, "\"\'?$<> |/");
	if (!len && !ft_strchr("\'\"?$<> |/", *str))
		len = ft_strlen(str);
	res = ft_strdup(ft_strchr(find_key_node(main->sort_env, "PWD")->data, '=') +
			1);
	res = find_env(main, str, len); //TODO: remove leak, not correct search return LDPWD instead of OLDPWD
	str += len;
	*string = str;
	if (*str == '$' && ++*string)
		res = ft_strdup("80085");
	else if (*str == '?' && ++*string)
		res = ft_itoa(main->exit_code);
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
