/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:51:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/14 20:22:28 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_add_char(char *string, char c)
{
	char	*res;
	int		len;

	len = ft_strlen(string);
	res = (char *)ft_realloc(string, len + 1, len + 2);
	res[len] = c;
	return (res);
}

