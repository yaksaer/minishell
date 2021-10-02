/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/10/01 20:44:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_main(t_main *main, char **envp)
{
	if (!main)
		return (1);
	// main->sort_env = copy_env_to_list(envp); //need to sort this list
	// if (!main->sort_env)
	// 	return (NULL);
	// main->env = copy_env_to_mass(envp);
	// if (!main->env)
	// 	return (NULL);
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	int		stop;
	t_main		*main;

	main = (t_main *)ft_calloc(1, sizeof(main));
	stop = 0;
	if (init_main(main, envp))
		return (1);
	while (!stop)
	{
		stop = parser(main);
	}
	ft_allocfree((void *)&main); //free & null if exist void ft_allocfree(void **data)
	return (0);
}