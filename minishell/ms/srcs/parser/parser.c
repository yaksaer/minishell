/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/10/18 13:00:35 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_word(t_main *main, char **string)
{
	char	*res;
	char	*str;

	str = *string;
	res = NULL;
	while (!ft_strchr(" \t<>|", *str) && *str != '\0')
	{
		if (ft_strchr(";\\", *str))
			re_parser(main, *str);
		else if (ft_strchr("\'\"", *str))
			res = ft_strjoinm(res, parse_quotation(main, &str, *str), 3);
		else if (*str == '$' && str[1] && !ft_strchr(" \t|", str[1]))
			res = ft_strjoinm(res, put_env(main, &str), 3);
		else
			res = ft_add_char(res, *str++);
	}
	*string = str;
	return (res);
}

int	parse_command(t_main *main, t_commands *command, char **string, char *res)
{
	char	*str;
	int		i;

	i = 0;
	str = *string;
	while (*str != '\0' && *str != '|')
	{
		if (ft_strchr("<>", *str))
		{
			if (res)
				command->cmd = add_string_to_massive(&command->cmd, &res, i++);
			parse_redirect(main, command, &str);
		}
		else
			res = parse_word(main, &str);
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
		i = parse_command(main, command, &string, NULL);
		if (i)
			string++;
		commands_back(&main->commands, command);
	}
}
int	parser(t_main *main)
{
	char		*str;
	t_commands	*temp;

	str = readline(BEGIN(49, 32)"Minishell: "CLOSE);
	if (!str)
	{
		write(1, "\rexit\n", 6);
		exit(0);
	}
	if (str)
		add_history(str);
	start_pars(main, str);
	if (main->commands->redir)
		handle_redir(main);
//	print_commands(main);
	ft_allocfree((void *)&str);
	return (1);
}
