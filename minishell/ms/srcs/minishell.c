/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/10/04 01:15:05 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_main(t_main *main, char **envp)
{
	if (!main)
		return (1);
	main->sort_env = copy_env_to_list(envp);
	if (!main->sort_env)
		return (1);
	sort_dlist(main->sort_env);
	main->env = copy_env_to_mass(envp);
	if (!main->env)
		return (1);
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
	stop = parser(main);
	get_command(main);
	ft_allocfree((void *)&main); //free & null if exist void ft_allocfree(void **data)
	return (0);
}