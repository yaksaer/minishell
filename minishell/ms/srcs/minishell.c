/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/10/18 13:26:23 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>

t_main	*g_main = NULL;

//обработать незакрытые скобки и спецсимволы
t_main	*init_main(char **envp)
{
	struct sigaction	sigac;

	g_main = (t_main *)malloc(sizeof(t_main));
	if (!g_main)
		return (NULL);
	g_main->sort_env = copy_env_to_list(envp);
	if (!g_main->sort_env)
		return (NULL);
	g_main->env = copy_env_to_mass(g_main->sort_env);
	if (!g_main->env)
		return (NULL);
	sort_dlist(g_main->sort_env);
	g_main->commands = NULL;
	g_main->sigac = sigac;
	g_main->exit_code = 0;
	add_to_list(g_main, "SHLVL=2", "SHLVL");
	return (g_main);
}

void	minishell(t_main *main)
{
	int	stop;

	stop = 1;
	while (stop)
	{
		if (redirect_signals(&main->sigac, "mc"))
			exit (1);
		stop = parser(main);
//		if (redirect_signals(&main->sigac, "m0"))
//			exit (1);
		get_command(main);
		commands_clear(&main->commands);
	}
	ft_dlist_del(&main->sort_env);
	ft_allocfree((void *)&main);
	exit (0);
}

int	main(int ac, char **av, char **envp)
{
	t_main	*main;

	main = init_main(envp);
	if (!main)
		return (1);
	minishell(main);
	return (0);
}
