/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/10/09 13:54:50y cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_commands(t_main *main)
{
	t_commands	*temp;
	int			i;

	temp = main->commands;
	i = 0;
	while (temp != NULL)
	{
		printf("%d pipe\n", i);
		printf("\ncmds:\n");
		for (int c = 0; temp->cmd && temp->cmd[c] != NULL; c++)
		{
			printf("%s\n", temp->cmd[c]);
		}
		printf("\nredirects:\n");
		for (int c = 0; temp->redir && temp->redir[c] != NULL; c++)
		{
			printf("%s\n", temp->redir[c]);
		}
		printf("\ninput = %d, output = %d\n", temp->input, temp->output);
		temp = temp->next;
		i++;
		write(1, "\n", 1);
	}
}

char	*ft_add_char(char *string, char c, int len)
{
	char	*res;
	res = (char *)ft_realloc(string, len + 1, len + 2);
	res[len] = c;
	return (res);
}
// check $'USER' $"US'ER"
char	*put_env(t_main *main, char **string)
{
	char	*res;
	char	*str;
	int		len;
	int		i;

	res = NULL;
	str = *string;
	str++;
	len = ft_strlen_until(str, "\"\'$<> |");
	if (!len)
		len = ft_strlen(str);
	i = 0;
	while (main->env[i] && (ft_strlen_until(main->env[i], "=") != len \
		|| ft_strncmp(str, main->env[i], len)))
	{
		printf("%s\n", main->env[i]);
		i++;
	}
	str += len;
	*string = str;
	if (main->env[i])
		res = ft_substr(main->env[i], len + 1, ft_strlen(main->env[i]));
	return (res);
}

char	*parse_quotation(t_main *main, char **string, char quote)
{
	char	*str;
	char	*res;

	str = *string;
	str++;
	res = NULL;
	while (*str != quote)
	{
		if (quote == '\"' && *str == '$' && !ft_strchr(" \t|", *str + 1)) 
			res = ft_strjoinm(res, put_env(main, &str), 3);
		else
			res = ft_add_char(res, *str++, ft_strlen(res));
	}
	str++;
	*string = str;
	return (res);
}

char	*parse_string(t_main *main, char **string)
{
	char	*res;
	char	*str;

	str = *string;
	res = NULL;
	while (!ft_strchr(" \t<>|", *str) && *str != '\0')
	{
		if (ft_strchr("\'\"", *str))
			res = ft_strjoinm(res, parse_quotation(main, &str, *str), 3);
		else if (*str == '$' && !ft_strchr(" \t|", *str + 1))
			res = ft_strjoinm(res, put_env(main, &str), 3);
		else
			res = ft_add_char(res, *str++, ft_strlen(res));
	}
	*string = str;
	return (res);
}

void	parse_redirect(t_main *main, t_commands *command, char **string)
{
	static int	i;
	char		*str;
	char		*res;

	if (!command->redir)
		i = 0;
	str = *string;
	res = NULL;
	while (ft_strchr("<>", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++, ft_strlen(res));
	while (ft_strchr(" \t", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++, ft_strlen(res));
	while (!ft_strchr(" \t<>", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++, ft_strlen(res));
	command->redir = add_string_to_massive(&command->redir, &res, i++);
	*string = str;
}

int	parse_command(t_main *main, t_commands *command, char **string)
{
	char	*str;
	char	*res;
	int		i;

	i = 0;
	str = *string;
	res = NULL;
	while (*str != '\0' && *str != '|')
	{
		if (ft_strchr("<>", *str))
		{
			if (res)
				command->cmd = add_string_to_massive(&command->cmd, &res, i++);
			parse_redirect(main, command, &str);
		}
		else
			res = parse_string(main, &str);
		if (ft_strchr(" \t", *str) || *str == '\0')
		{
			if (res)
				command->cmd = add_string_to_massive(&command->cmd, &res, i++);
			str += ft_strlen_while(str, " \t");
		}
	}
	*string = str;
	return (ft_ter_i(*str == '|', 1, 0));
}

void	start_pars(t_main *main, char *string)
{
	t_commands	*command;
	int			i;

	i = 1;
	while (i)
	{
		command = commands_new(NULL, NULL, 0, 0);
		string += ft_strlen_while(string, " \t");
		i = parse_command(main, command, &string);
		if (i)
			string++;
		commands_back(&main->commands, command);
	}
}

int	open_redir(char *path, char r, int n)
{
	int fd;

	if (r == '>')
	{
		if (n == 1)
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0064);
		else
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0664);
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
	res = parse_string(main, &path);
	fd = open_redir(res, r, num);
	if ((r == '>' && com->output != 0) || (r == '<' && com->input != 0))
		ft_ter_i(r == '>', close(com->output), close(com->input));
	if (r == '>')
		com->output = fd;
	else if (r == '<')
		com->input = fd;
}

char	*parse_heredoc(char *str, int *q, int *t)
{
	char	*res;

	res = NULL;
	*t = ft_ter_i(str[2] == '-', 1, 0);
	str += 3;
	str += ft_strlen_while(str, " \t");

	return (res);
}

char	*ft_heredoc(t_commands *com, char *string)
{
	char	*str;
	char	*res;
	char	*key;
	int		quot_flag;
	int		tab_flag;

	res = NULL;
	key = parse_heredoc(string, &quot_flag, &tab_flag);
	while (1)
	{
		str = readline("heredoc: ");
		if (!ft_strcmp(key, str))
		{
			ft_allocfree((void *)&str);
			break ;
		}
		str = ft_add_char(str, '\n', ft_strlen(str));
		res = ft_strjoinm(res, str, 3);
	}
	ft_allocfree((void *)&key);
	return (res);
}

size_t	ft_strlen_while(const char *string, const char *smls)
{
	size_t	len;

	len = 0;
	if (string && smls)
	{
		while (string[len] != '\0' && ft_strchr(smls, string[len]))
			len++;
	}
	return (len);
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
				com->redir[i] = ft_strrepl(com->redir[i], \
					ft_heredoc(com, com->redir[i]));
		}
		com = com->next;
	}
}

int	parser(t_main *main) // здесь нужно отработать ошибки
{
	char		*str;
	t_commands	*temp;

	str = readline(BEGIN(49, 32)"Minishell: "CLOSE);
	if (str)
		add_history(str);
 	if (str[0] == 'q')
	{
		free(str);
		return (0);
	}
	start_pars(main, str);
	if (main->commands->redir)
		handle_redir(main);
	print_commands(main);
	ft_allocfree((void *)&str);
	return (1);
}
