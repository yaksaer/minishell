/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/09/29 16:45:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_main(t_main **main, char **envp)
{
	*main = (t_main *)ft_calloc(1, sizeof(main));
	if (!*main)
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
	t_main	*main;
	int		stop;

	stop = 0;
	if (init_main(&main, envp))
		return (1);
	while (!stop)
	{
		stop = parser(main);
	}
	ft_allocfree((void *)&main); //free & null if exist void ft_allocfree(void **data)
	return (0);
}