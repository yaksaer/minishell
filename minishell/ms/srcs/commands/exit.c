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
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			command->cmd[1]);
		exit(255);
	}
	i = 0;
	while (command->cmd[1][++i])
	{
		if (!ft_isdigit(command->cmd[1][i]))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				command->cmd[1]);
			exit(255);
		}
	}
}

int	count_commands(t_main *main)
{
	t_commands	*tmp;
	int			i;

	i = 0;
	tmp = main->commands;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_exit(t_main *main, t_commands *command)
{
	if (count_commands(main) > 1)
		return (0);
	if (ft_mass_size(command->cmd) == 1)
	{
		printf("exit\n");
		exit(0);
	}
	numeric_exit(command);
	if (ft_mass_size(command->cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	printf("exit\n");
	exit(ft_atoi(command->cmd[1]));
	return (0);
}
