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

int	ft_skip_spaces(const char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	return (i);
}

static long long	ft_exit_atoi(const char *nptr)
{
	size_t			i;
	unsigned long	num;
	unsigned long	max;
	int				zn;

	num = 0;
	zn = 1;
	max = (unsigned long)(__LONG_LONG_MAX__ / 10);
	i = ft_skip_spaces(nptr, 0);
	if (nptr[i] == '-')
		zn = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((num > max || (num == max && (nptr[i] - '0') > 7))
			&& zn == 1)
			return (0);
		else if ((num > max || (num == max && (nptr[i] - '0') > 8))
			&& zn == -1)
			return (0);
		num = (10 * num) + (nptr[i] - '0');
		i++;
	}
	return ((long long)(num * zn));
}

void	numeric_exit(t_commands *command, int flag)
{
	int	i;

	if ((!ft_isdigit(command->cmd[1][0]) && command->cmd[1][0] != '-'
		&& command->cmd[1][0] != '+') || flag == 1)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			command->cmd[1]);
		free_all(NULL, NULL);
		exit(255);
	}
	i = 0;
	while (command->cmd[1][++i])
	{
		if (!ft_isdigit(command->cmd[1][i]))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				command->cmd[1]);
			free_all(NULL, NULL);
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
	unsigned char	c;
	long long		num;

	if (count_commands(main) > 1)
		return (0);
	if (ft_mass_size(command->cmd) == 1)
	{
		printf("exit\n");
		free_all(NULL, NULL);
		exit(0);
	}
	numeric_exit(command, 0);
	if (ft_mass_size(command->cmd) > 2)
		printf("minishell: exit: too many arguments\n");
	num = ft_exit_atoi(command->cmd[1]);
	if (num == 0 && ft_strlen(command->cmd[1]) > 1 && command->cmd[1][0] != '0')
		numeric_exit(command, 1);
	c = num;
	printf("exit\n");
	free_all(NULL, NULL);
	exit(c);
	return (0);
}
