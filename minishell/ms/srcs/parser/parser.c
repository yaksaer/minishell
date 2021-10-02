/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/10/02 01:36:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_add_char(char *string, char c, int len)
{
	string = (char *)ft_realloc(string, len + 1, len + 2);
	string[len] = c;
	return (string);
}

char *parse_quotation(char **string, char quote)
{
	char	*str;
	char	*res;

	str = *string;
	str++;
	res = NULL;
	while (*str != quote)
	{
		if (*str == '|' || *str == '\0')
		{
			printf("Error: in quotation meet | or \\0\n");
			exit (1);
		}
		/*if (*str == '$') написать функцию для доллара*/
		res = ft_add_char(res, *str++, ft_strlen(res));
	}
	str++;
	*string = str;
	return (res);
}

void	parse_redirect(t_commands *command, char **string)
{
	static int	i = 0;
	char		*str;
	char		*res;
	
	str = *string;
	res = NULL;
	while (ft_strchr("<>", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++, ft_strlen(res));	
	while (ft_strchr(" \t", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++, ft_strlen(res));
	while (!ft_strchr(" \t", *str) && *str != '|' && *str != '\0')
		res = ft_add_char(res, *str++, ft_strlen(res));
	if (*str == '|' || *str == '\0')
	{
		printf("Error: in redirect meet | or \\0\n");
		exit (1);
	}		
	command->redir = add_string_to_massive(command->redir, res, i++);
	res = NULL;
	*string = str;
}

int	preparsing(t_commands *command, char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while (*str != '\0' || *str != '|')
	{
		if (ft_strchr("\'\"", *str))
			res = ft_strjoinm(res, parse_quotation(&str, *str), 3);
		/*if (*str == '$') написать функцию для доллара*/
		else if (ft_strchr("<>", *str))
		{
			command->cmd = add_string_to_massive(command->cmd, res, i++);
			res = NULL;
			parse_redirect(command, &str);
		}
		else
			res = ft_add_char(res, *str++, ft_strlen(res));
		if (ft_strchr(" \t", *str))
		{
			if (res)
				command->cmd = add_string_to_massive(command->cmd, res, i++);
			res = NULL;
			str += ft_strlen_while(str, " \t");
		}
	}
	return (ft_ter_i(*str == '|', 1, 0));
}

void	start_pars(t_main *main, char *string)
{
	int	pipe;
	t_commands *command;
	
	pipe = 1;
	while (pipe)
	{
		command = commands_new(NULL, NULL, -1, -1);
		pipe = preparsing(command, string);
		if (pipe)
			string += ft_strlen_until(string, "|");
		commands_back(&main->commands, command);
	}
}

int	parser(t_main *main) // здесь нужно отработать ошибки
{
	char		*str;

	str = readline(BEGIN(49, 32)"Minishell: "CLOSE);
	if (str[0] == 'q')
	{
		free(str);
		return (1);
	}
	start_pars(main, str);
	ft_allocfree((void *)&str);
	return (0);
}