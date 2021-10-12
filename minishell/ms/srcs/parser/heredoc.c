/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:14:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/12 19:56:21 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	her_signals(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		kill(info->si_pid, SIGKILL);
	}
}

char	*parse_heredoc(char *str, int *qt)
{
	char	*res;

	res = NULL;
	*qt = ft_ter_i(str[2] == '-', 2, *qt);
	str = ft_ter_s(*qt & 2, str + 3, str + 2);
	str += ft_strlen_while(str, " \t");
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str) && *str++ && ++*qt)
			continue ;
		res = ft_add_char(res, *str++, ft_strlen(res));
	}
	return (res);
}

char	*put_heredoc(t_main *main, char *dest, char *src, int qt)
{
	char	*res;

	res = NULL;
	if (qt & 2)
		src += ft_strlen_while(src, "\t");
	while (*src != '\0')
	{
		if (*src == '$' && !(qt & 1))
			res = ft_strjoinm(res, put_env(main, &src), 3);
		else
			res = ft_add_char(res, *src++, ft_strlen(res));
	}
	res = ft_add_char(res, '\n', ft_strlen(res));
	res = ft_strjoinm(dest, res, 3);
	return (res);
}

int	heredoc_process(t_main *main, char *key, char *string, int qt)
{
	char				*str;
	char				*res;
	struct sigaction	her;

	her.sa_flags = SA_SIGINFO;
	her.sa_sigaction = her_signals;
	if (sigaction(SIGQUIT, &her, 0) == -1 || sigaction(SIGINT, &her, 0) == -1)
		exit (EXIT_FAILURE);
	res = NULL;
	while (1)
	{
		str = readline("heredoc: ");
		if (!str)
			exit (EXIT_SUCCESS);
		if (!ft_strcmp(key, str))
		{
			ft_allocfree((void *)&str);
			break ;
		}
		res = put_heredoc(main, res, str, qt);
	}
	qt = open_redir(".heredoc", '>', 1);
	write(qt, res, ft_strlen(res));
	ft_allocfree((void *)&res);
	return (qt);
}

void	ft_heredoc(t_main *main, t_commands *com, char *string)
{
	char	*key;
	int		quo_tab_flags;
	int		pid;
	int		input;

	quo_tab_flags = 0;
	key = parse_heredoc(string, &quo_tab_flags);
	pid = fork();
	if (pid == 0)
		input = heredoc_process(main, key, string, quo_tab_flags);
	wait(NULL);
	ft_allocfree((void *)&key);
	if (com->input != 0)
		close(com->input);
	com->input = input;
	return ;
}
