/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/10/04 01:13:01 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_commands(t_main *main)
{
	t_commands *temp;

	temp = main->commands;
	int i = 1;
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
		/*if (*str == '$') написать функцию для доллара*/
		res = ft_add_char(res, *str++, ft_strlen(res));
	}
	str++;
	*string = str;
	return (res);
}

void	parse_redirect(t_commands *command, char **string)
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
	{
		if (ft_strchr("\'\"", *str))
			res = ft_strjoinm(res, parse_quotation(&str, *str), 3);
		else	
			res = ft_add_char(res, *str++, ft_strlen(res));
	}
	command->redir = add_string_to_massive(command->redir, res, i++);
	res = NULL;
	*string = str;
}



int	parse_command(t_commands *command, char **string)
{
	char	*str;
	char	*res;
	int		i;

	i = 0;
	str = *string;
	res = NULL;
	while (*str != '\0' && *str != '|')
	{
		if (ft_strchr("\'\"", *str))
			res = ft_strjoinm(res, parse_quotation(&str, *str), 3);
		/*if (*str == '$') написать функцию для доллара*/
		else if (ft_strchr("<>", *str))
		{
			if (res)
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
		i = parse_command(command, &string);
		if (i)
			string++;
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
	print_commands(main);
	ft_allocfree((void *)&str);
	return (0);
}
