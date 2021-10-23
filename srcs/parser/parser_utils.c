/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:51:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/21 20:24:45 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_commands	*change_command(t_main *main, t_commands *cmd)
{
	t_commands	*temp;
	t_commands	*tmp;
	int			i;

	i = 0;
	temp = main->commands;
	tmp = temp;
	if (temp == cmd)
		main->commands = main->commands->next;
	while (temp && i == 0)
	{
		if (temp == cmd && ++i)
		{
			tmp->next = temp->next;
			commands_delone(cmd);
			break ;
		}
		tmp = temp;
		temp = temp->next;
	}
	return (tmp->next);
}

char	*ft_add_char(char *string, char c)
{
	char	*res;
	int		len;

	len = ft_strlen(string);
	res = (char *)ft_realloc(string, len + 1, len + 2);
	res[len] = c;
	return (res);
}

void	check_pipe(t_main *main, t_commands *com)
{
	if (!com->cmd && !com->redir && main->commands)
		re_parser(main, '|');
}

void	re_parser(t_main *main, char c)
{
	main->exit_code = 1;
	main->flag_exit = 1;
	if (c == 's')
	{
		write(1, "Minishell: Syntax error\n", 25);
		errno = 0;
		main->exit_code = 258;
	}
	else if (c == '\'' || c == '\"')
		printf("Minishell: %c : Unclosed quotes\n", c);
	else if (c == ';' || c == '\\')
		printf("Minishell: '%c' : Unknown character\n", c);
	else if (c == '|')
		printf("Minishell: '%c' : No command after pipe\n", c);
	commands_clear(&main->commands);
	minishell(main);
}
