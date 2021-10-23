/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:14:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/22 19:51:57 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_heredoc(char *str, int *qt)
{
	char	*res;
	char	err;

	res = NULL;
	*qt = ft_ter_i(str[2] == '-', 2, *qt);
	str = ft_ter_s(*qt & 2, str + 3, str + 2);
	str += ft_strlen_while(str, " \t");
	while (*str != '\0')
	{
		err = *str;
		if (ft_strchr("\'\"", *str) && *str++ && ++*qt)
			continue ;
		res = ft_add_char(res, *str++);
	}
	if (!res)
		re_parser(g_main, 's');
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
			res = ft_add_char(res, *src++);
	}
	res = ft_add_char(res, '\n');
	res = ft_strjoinm(dest, res, 3);
	return (res);
}

void	heredoc_process(t_main *main, char *key, int qt, int input)
{
	char				*str;
	char				*res;
	struct sigaction	her;

	str = NULL;
	redirect_signals(&her, "hc");
	res = NULL;
	while (1)
	{
		str = readline("heredoc: ");
		if (!ft_strcmp(key, str))
		{
			ft_allocfree((void *)&str);
			break ;
		}
		res = put_heredoc(main, res, str, qt);
	}
	write(input, res, ft_strlen(res));
	close(input);
	ft_allocfree((void *)&res);
	exit (0);
}

void	ft_heredoc(t_main *main, int *input, char *string)
{
	char	*key;
	int		quo_tab_flags;
	int		pid;
	int		inp;
	int		status;

	quo_tab_flags = 0;
	key = parse_heredoc(string, &quo_tab_flags);
	redirect_signals(&main->sigac, "m0");
	inp = open_redir(ft_strdup(key), '>', 1);
	pid = fork();
	if (pid == 0)
		heredoc_process(main, key, quo_tab_flags, inp);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1 && ++main->flag_exit)
		main->exit_code = 1;
	redirect_signals(&main->sigac, "mc");
	if (*input != 0)
		close(*input);
	inp = open_redir(key, '<', 1);
	unlink(key);
	*input = inp;
	return ;
}
