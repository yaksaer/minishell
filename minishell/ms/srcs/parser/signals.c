/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:50 by marvin            #+#    #+#             */
/*   Updated: 2021/10/14 19:46:32 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_main->exit_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
		g_main->exit_code = 131;
	}
}

void	handle_signals(int sig, siginfo_t *info, void *ucontext)
{
	siginfo_t	*usl;
	void		*usls;

	usl = info;
	usls = ucontext;
	if (g_main->pid != -1)
		cmd_signals(sig);
	else if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_main->exit_code = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

void	her_signals(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		exit (1);
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

void	switsch_signals(t_main *main, t_commands *command)
{
	t_commands	*cmd;
	int			i;
	int			a;

	cmd = command;
	a = 0;
	i = -1;
	while (command && command->cmd && cmd->cmd[++i])
	{
		if (!ft_strcmp(cmd->cmd[i], "./minishell"))
		{
			a = 1;
			break ;
		}
	}
	if (a == 1)
		redirect_signals(&main->sigac, "m0");
}

void	redirect_signals(struct sigaction *sigac, char *s)
{
	sigac->sa_mask = 0;
	if (ft_strchr(s, 'c'))
	{
		if (ft_strchr(s, 'm'))
		{	
			sigac->sa_flags = SA_SIGINFO;
			sigac->sa_sigaction = handle_signals;
		}
		else if (ft_strchr(s, 'h'))
			sigac->sa_sigaction = her_signals;
	}
	if (ft_strchr(s, '0'))
		sigac->sa_handler = SIG_IGN;
	else if (ft_strchr(s, '1'))
		sigac->sa_handler = SIG_DFL;
	if (ft_strchr(s, 'h'))
		sigac->sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, sigac, 0) == -1)
		 exit (1);
	if (sigaction(SIGQUIT, sigac, 0) == -1)
		exit (1);
}
