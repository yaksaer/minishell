/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:45:10 by marvin            #+#    #+#             */
/*   Updated: 2021/10/22 20:06:30 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_word(t_main *main, char **string)
{
	char		*res;
	char		*str;

	str = *string;
	res = NULL;
	while (main->var || (!ft_strchr(" \t<>|", *str) && *str != '\0'))
	{
		if (main->var)
		{
			res = ft_strjoinm(res, parse_var(main), 3);
			break ;
		}
		if (ft_strchr("\'\"", *str))
			res = ft_strjoinm(res, parse_quotation(main, &str, *str), 3);
		else if (*str == '$' && str[1] && !ft_strchr(" \t|", str[1]))
			main->var = put_env(main, &str);
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
	while ((*str != '\0' && *str != '|') || main->var)
	{
		if (!main->var && ft_strchr("<>", *str))
		{
			if (res)
				command->cmd = add_string_to_massive(&command->cmd, &res, i++);
			parse_redirect(command, &str);
		}
		else
			res = ft_strjoinm(res, parse_word(main, &str), 3);
		if (ft_strchr(" \t", *str) || *str == '\0')
		{
			if (res)
				command->cmd = add_string_to_massive(&command->cmd, &res, i++);
			str += ft_strlen_while(str, " \t");
		}
	}
	*string = str;
	check_pipe(main, command);
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
		if (main->flag_exit == 1)
		{
			main->flag_exit = 0;
			main->exit_code = 0;
		}
	}
}

/*print_commands(main);
Add after handle redir for debug parser*/

int	parser(t_main *main)
{
	char		*str;

	str = readline(BEGIN"Minishell: "CLOSE);
	if (!str)
	{
		write(1, BEGIN"\033[AMinishell: "CLOSE, 31);
		write(1, "exit\n", 6);
		rl_redisplay();
		tcsetattr(STDIN_FILENO, TCSANOW, &g_main->oldterm);
		free_all(NULL, NULL);
		exit(0);
	}
	if (str)
		add_history(str);
	start_pars(main, str);
	handle_redir(main);
	ft_allocfree((void *)&str);
	if (!main->commands)
		re_parser(main, 0);
	return (1);
}
