/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/09/28 15:13:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		init_main(t_main *main, char **envp)
{
	main->sort_env = copy_env_to_list(envp); //need to sort this list
	if (!main->sort_env)
		return (1);
	main->env = copy_env_to_mass(envp);
	if (!main->env)
		return (1);
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	//t_ms	*ms;
	t_main	main;

	ft_bzero(&main, sizeof(t_main));
	if (init_main(&main, envp))
		return (1);
	return (0);
}