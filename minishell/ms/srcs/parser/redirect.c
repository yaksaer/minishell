/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:54:58 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/14 21:23:26 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_redirect(t_main *main, t_commands *cmd, char **string)
{
	static int	i;
	char		*str;
	char		*res;

	if (!cmd->redir)
		i = 0;
	str = *string;
	res = NULL;
	while (ft_strchr("<>", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++);
	if (!ft_strcmp(res, "<<") && *str == '-')
		res = ft_add_char(res, *str++);
	while (ft_strchr(" \t", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++);
	while (!ft_strchr(" \t<>", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++);
	cmd->redir = add_string_to_massive(&cmd->redir, &res, i++);
	*string = str;
}

int	open_redir(char *path, char r, int n)
{
	int fd;

	if (r == '>')
	{
		if (n == 1)
			fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0664);
		else
			fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0664);
	}
	else
	{
		if (n == 1)
			fd = open(path, O_RDONLY, 0664);
	}
	if (fd == -1)
	{
		printf("wrong path of redirect\n");
		exit (1);
	}
	return (fd);
}

void	redir_path(t_main *main, t_commands *com, char *path, char r)
{
	int		fd;
	char	*res;
	int		num;

	res = NULL;
	num = ft_strlen_while(path, ">");
	if (!num)
		num = 1;
	path += num;
	path += ft_strlen_while(path, " \t");
	res = parse_word(main, &path);
	fd = open_redir(res, r, num);
	if ((r == '>' && com->output != 0) || (r == '<' && com->input != 0))
		ft_ter_i(r == '>', close(com->output), close(com->input));
	if (r == '>')
		com->output = fd;
	else if (r == '<')
		com->input = fd;
}

void handle_redir(t_main *main) //прикрутить проверку на количество стрелок
{
	t_commands	*com;
	char		r;
	int			i;

	com = main->commands;
	while (com)
	{
		i = -1;
		while (com->redir[++i])
		{
			r = com->redir[i][0];
			if (ft_strlen_while(com->redir[i], ">") == 1 || \
				ft_strlen_while(com->redir[i], ">") == 2 || \
				ft_strlen_while(com->redir[i], "<") == 1)
				redir_path(main, com, com->redir[i], r);
			else if (ft_strlen_while(com->redir[i], "<") == 2)
				ft_heredoc(main, com, com->redir[i]);
		}
		com = com->next;
	}
}
