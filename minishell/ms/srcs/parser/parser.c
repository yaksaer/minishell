/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/09/30 18:04:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_string(t_main *main, char *str)
{
	t_commands *command;

	while ()
}

int	parser(t_main *main)
{
	char	*str;
	t_commands *command;

	str = readline(BEGIN(49, 32)"Minishell: "CLOSE);
	if (str[0] == 'q')
	{
		free(str);
		return (1);
	}
	while
	printf("%s\n", str);
	handle_string(main, str);
	ft_allocfree((void *)&str);
	return (0);
}