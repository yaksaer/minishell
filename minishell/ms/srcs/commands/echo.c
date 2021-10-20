/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:31 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:32 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(int argc, char **argv)
{
	bool	n_option;
	int		i;

	n_option = false;
	if (argc == 1)
		printf("\n");
	i = 1;
	if (argc >= 2 && ft_strlen(argv[1]) == 2
		&& !ft_strncmp(argv[1], "-n", 2))
	{
		n_option = true;
		i++;
	}
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		i++;
	while (i < argc)
	{
		ft_putstr_fd(argv[i++], 1);
		if (i == argc && !n_option)
			ft_putchar_fd('\n', 1);
		else if (i < argc)
			ft_putchar_fd(' ', 1);
	}
	return (0);
}
