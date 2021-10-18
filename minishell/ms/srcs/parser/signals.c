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

void	handle_signals(int sig, siginfo_t *info, void *ucontext)
{
	static int	pid;
	siginfo_t	*usl;
	void		*usls;

	usl = info;
	usls = ucontext;
	if (sig == SIGINT) // Нужна глобалка для ошибок
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_main->exit_code = 130;
	}
	else if (sig == SIGQUIT) //нужно в cat прочитать ^\'
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

void	her_signals(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		exit (1);
	}
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

int redirect_signals(struct sigaction *sigac, char *s)
{
	if (ft_strchr(s, 'c'))
	{
		if (ft_strchr(s, 'm'))
		{	
			sigac->sa_flags = SA_SIGINFO;
			sigac->sa_sigaction = handle_signals;
		}
		else if (ft_strchr(s, 'h'))
		{
			sigac->sa_flags = SA_RESETHAND;
			sigac->sa_sigaction = her_signals;
		}
	}
	if (ft_strchr(s, '0'))
		sigac->sa_handler = SIG_IGN;
	else if (ft_strchr(s, '1'))
		sigac->sa_handler = SIG_DFL;
	if (sigaction(SIGINT, sigac, 0) == -1)
		 return (1);
	if (ft_strchr(s, 'h'))
		sigac->sa_flags = SA_SIGINFO;
	if (sigaction(SIGQUIT, sigac, 0) == -1)
		return (1);
	return (0);
}