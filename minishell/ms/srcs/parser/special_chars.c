/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:58:22 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/15 19:42:49 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// check $'USER' $"US'ER"
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
	while (main->env[i] && (ft_strlen_until(main->env[i], "=") != len \
		|| ft_strncmp(str, main->env[i], len)))
		i++;
	str += len;
	*string = str;
	if (main->env[i])
		res = ft_substr(main->env[i], len + 1, ft_strlen(main->env[i]));
	if ((*str == '$' && ++*string) || (*str == '?' && ++*string))
		res = ft_ter_s(*str == '$', ft_strdup("80085"), \
									ft_itoa(main->exit_code));
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
