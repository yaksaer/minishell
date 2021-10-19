/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:47 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:48 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	path[1024];

	ft_bzero(path, FILENAME_MAX);
	if (getcwd(path, FILENAME_MAX) == NULL)
		return (1);
	printf("%s\n", path);
	return (0);
}
