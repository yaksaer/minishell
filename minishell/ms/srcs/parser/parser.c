/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/10/07 15:08:40 by cbilbo           ###   ########.fr       */
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
		temp = temp->next;
		i++;
		write(1, "\n", 1);
	}
}

char	*ft_add_char(char *string, char c, int len)
{
	string = (char *)ft_realloc(string, len + 1, len + 2);
	string[len] = c;
	return (string);
}

size_t	ft_strlen_until(const char *string, const char *smls)
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = 0;
	i = -1;
	while (smls[++i])
	{
		j = -1;
		while (string[++j])
		{
			if (string[j] == smls[i])
			{
				if (j < len || len == 0)
					len = j;
				break ;
			}
		}
	}
	return (len);
}

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
		i++;
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
		if (quote == '\"' && *str == '$' && !ft_strchr(" \t|", str + 1))
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
		else if (*str == '$' && !ft_strchr(" \t|", str + 1))
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
		res = ft_strjoinm(res, parse_string(main, &str), 3);
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
		command = commands_new(NULL, NULL, -1, -1);
		string += ft_strlen_while(string, " \t");
		i = parse_command(main, command, &string);
		if (i)
			string++;
		commands_back(&main->commands, command);
	}
}

int	parser(t_main *main) // здесь нужно отработать ошибки
{
	char		*str;
	t_commands	*temp;

	str = readline(BEGIN(49, 32)"Minishell: "CLOSE);
	if (str[0] == 'q')
	{
		free(str);
		return (0);
	}
	start_pars(main, str);
	print_commands(main);
	ft_allocfree((void *)&str);
	return (1);
}
