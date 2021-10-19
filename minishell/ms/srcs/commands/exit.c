/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:37 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:38 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	numeric_exit(t_commands *command)
{
	int	i;

	if (!ft_isdigit(command->cmd[1][0]) && command->cmd[1][0] != '-'
		&& command->cmd[1][0] != '+')
	{
		printf("minishell: exit: %s: numeric argument required\n",
			   command->cmd[1]);
		exit(255);
	}
	i = 0;
	while (command->cmd[1][++i])
	{
		if (!ft_isdigit(command->cmd[1][i]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				   command->cmd[1]);
			exit(255);
		}
	}
	exit(ft_atoi(command->cmd[1]));
}

int	ft_exit(t_commands *command)
{
	if (ft_mass_size(command->cmd) == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (ft_mass_size(command->cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else
		numeric_exit(command);
	return (0);
}
