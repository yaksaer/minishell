/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_while.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 23:48:03 by marvin            #+#    #+#             */
/*   Updated: 2021/10/02 00:00:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_while(const char *string, const char *smls)
{
	size_t	len;
	
	len = 0;
	if (string && smls)
	{
		while (string[len] != '\0' && ft_strchr(smls, string[len]))
			len++;
	}
	return (len);
}
