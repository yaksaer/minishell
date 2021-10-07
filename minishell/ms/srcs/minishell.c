/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/10/07 13:52:26 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_signals(int sig, siginfo_t *info, void *ucontext)
{
	siginfo_t	*usl;
	void		*usls;

	usl = info;
	usls = ucontext;
	if (sig == SIGINT)
		printf("hello Ctrl+C\n");
}

int	init_main(t_main *main, struct sigaction *sigac, char **envp)
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
	main->commands = NULL;
	sigac->sa_flags = SA_SIGINFO;
	sigac->sa_sigaction = handle_signals;
	return (0);
}

void	free_commands(t_commands *command)
{
	t_commands *tmp;

	tmp = command;
}

int		main(int ac, char **av, char **envp)
{
	int					stop;
	t_main				*main;
	struct sigaction	sigac;

	main = (t_main *)ft_calloc(1, sizeof(t_main));
	stop = 1;
	if (init_main(main, &sigac, envp))
		return (1);
	if (sigaction(SIGTSTP, &sigac, 0) == -1 || sigaction(SIGINT, &sigac, 0) == -1)
	{
		exit (EXIT_FAILURE);
	}
	while (stop)
	{
		stop = parser(main);
		get_command(main);
		commands_clear(&main->commands);
	}
	while (main->env[++stop])
		ft_allocfree((void *)&main->env[stop]);
	ft_dlist_del(&main->sort_env);
	ft_allocfree((void *)&main); //free & null if exist void ft_allocfree(void **data)
	return (0);
}