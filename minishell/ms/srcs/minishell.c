/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/10/15 19:41:51 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>

//обработать незакрытые скобки и спецсимволы
int	init_main(t_main *main, char **envp)
{
	struct sigaction	sigac;

	if (!main)
		return (1);
	main->sort_env = copy_env_to_list(envp);
	if (!main->sort_env)
		return (1);
	sort_dlist(main->sort_env);
	main->env = NULL;
	main->commands = NULL;
	main->sigac = sigac;
	main->exit_code = 0;
	add_to_list(main, "SHLVL=2", "SHLVL");
	return (0);
}

void	free_commands(t_commands *command)
{
	t_commands *tmp;

	tmp = command;
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
		if (redirect_signals(&main->sigac, "m0"))
			exit (1);
		get_command(main);
		commands_clear(&main->commands);
	}
	while (main->env[++stop])
		ft_allocfree((void *)&main->env[stop]);
	ft_dlist_del(&main->sort_env);
	ft_allocfree((void *)&main);
	exit (0);
}

int	main(int ac, char **av, char **envp)
{
	t_main	*main;

	main = (t_main *)ft_calloc(1, sizeof(t_main));
	if (init_main(main, envp))
		return (1);
	minishell(main);
	return (0);
}
