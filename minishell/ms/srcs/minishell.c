/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:11:35 by marvin            #+#    #+#             */
/*   Updated: 2021/10/22 18:39:44 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_main	*g_main = NULL;

void	free_all(void *buf, void **buf2)
{
	free_dmass((char **)buf2);
	if (buf)
		free(buf);
	ft_dlist_del(&g_main->sort_env);
	ft_dlist_del(&g_main->unsort_env);
	free_dmass(g_main->env);
	commands_clear(&g_main->commands);
	ft_allocfree(((void *)&g_main));
}

void	error_n_exit(void *buf, void **buf2, int flag)
{
	if (flag == 1)
		printf("Minishell: malloc error\n");
	free_all(buf, buf2);
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
	char	*tmp;

	g_main = (t_main *)malloc(sizeof(t_main));
	if (!g_main)
		return (NULL);
	tcgetattr(STDIN_FILENO, &g_main->term);
	g_main->oldterm = g_main->term;
	g_main->term.c_lflag &= ~ECHOCTL;
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
	tmp = ft_strdup("OLDPWD");
	add_to_list(g_main->sort_env, tmp, "OLDPWD");
	list_unset(g_main->unsort_env, "OLDPWD");
	g_main->commands = NULL;
	g_main->vault_pwd = NULL;
	g_main->flag_exit = 0;
	g_main->exit_code = 0;
	g_main->flag = 0;
	g_main->var = NULL;
	proc_shlvl(g_main);
	return (g_main);
}

void	minishell(t_main *main)
{
	int	stop;

	stop = 1;
	while (stop)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_main->term);
		main->pid = -1;
		main->flag_exit = 0;
		redirect_signals(&main->sigac, "mc");
		stop = parser(main);
		tcsetattr(STDIN_FILENO, TCSANOW, &g_main->oldterm);
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
