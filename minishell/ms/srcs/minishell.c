/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/10/19 16:55:51 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_main	*g_main = NULL;

void	error_n_exit(void *buf, void**buf2, int flag)
{
	if (flag == 1)
		printf("Minishell: malloc error\n");
	ft_allocfree(buf2);
	if (buf)
		free(buf);
	ft_dlist_del(&g_main->sort_env);
	ft_dlist_del(&g_main->unsort_env);
	ft_allocfree((void **)g_main->env);
	commands_clear(&g_main->commands);
	exit(1);
}

int	ft_mass_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_main	*init_main(char **envp)
{
	g_main = (t_main *)malloc(sizeof(t_main));
	if (!g_main)
		return (NULL);
	g_main->sort_env = copy_env_to_list(envp);
	if (!g_main->sort_env)
		return (NULL);
	g_main->unsort_env = copy_env_to_list(envp);
	if (!g_main->unsort_env)
		return (NULL);
	g_main->env = copy_env_to_mass(g_main->sort_env);
	if (!g_main->env)
		return (NULL);
	sort_dlist(g_main->sort_env);
	g_main->commands = NULL;
	g_main->exit_code = 0;
	proc_shlvl(g_main);
	return (g_main);
}

void	minishell(t_main *main)
{
	int	stop;

	stop = 1;
	while (stop)
	{
		main->pid = -1;
		redirect_signals(&main->sigac, "mc");
		stop = parser(main);
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

	(void)ac;
	(void)av;
	main = init_main(envp);
	if (!main)
		return (1);
	minishell(main);
	return (0);
}
