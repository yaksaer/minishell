/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:14:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/14 20:23:22 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		res = ft_add_char(res, *str++);
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
			res = ft_add_char(res, *src++);
	}
	res = ft_add_char(res, '\n');
	res = ft_strjoinm(dest, res, 3);
	return (res);
}

int	heredoc_process(t_main *main, char *key, char *string, int qt)
{
	char				*str;
	char				*res;
	struct sigaction	her;

	str = NULL;
	if (redirect_signals(&her, "hc"))
		exit (1);
	res = NULL;
	while (1)
	{
		str = readline("heredoc: ");
		while (!str)
			str = readline("");
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
	int		status;

	quo_tab_flags = 0;
	key = parse_heredoc(string, &quo_tab_flags);
	if (redirect_signals(&main->sigac, "m0"))
		exit (1);
	pid = fork();
	if (pid == 0)
		input = heredoc_process(main, key, string, quo_tab_flags);
	waitpid(pid, &status, 0);
	if (redirect_signals(&main->sigac, "mc"))
		exit (1);
	ft_allocfree((void *)&key);
	if (com->input != 0)
		close(com->input);
	com->input = input;
	return ;
}
