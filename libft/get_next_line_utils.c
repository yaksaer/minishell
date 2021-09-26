/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:44:35 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 15:55:30 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_end(int byte, char **remem)
{
	if (byte == 0)
		ft_free(*remem, 2);
	if (byte != 0)
	{
		*remem = make_remem(*remem);
		if (!remem)
			return (ft_free(*remem, 1));
	}
	if (byte > 0)
		return (1);
	return (0);
}
