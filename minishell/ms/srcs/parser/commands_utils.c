/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:44:37 by marvin            #+#    #+#             */
/*   Updated: 2021/09/30 18:54:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**add_string_to_massive(char **dest, char *src, int number)
{
	dest = (char **)ft_realloc(dest, (number + 1) * sizeof(dest), \
			(number + 2) * sizeof(dest));
	dest[number] = src;
	return (dest);
}

t_commands	*commands_new(char **cmd, char **redir, int input, int output)
{
	t_commands *new;
	
	new = (t_commands *)malloc(1 * sizeof(t_commands));
	if (!new)
		return (new);
	new->cmd = cmd;
	new->redir = redir;
	new->input = input;
	new->output = output;
	new->next = NULL;
	return (new);
}

void	commands_back(t_commands **command, t_commands *new)
{
	t_commands *com;

	com = *command;
	if (!new)
		return ;
	if (!com)
		*command = new;
	else
	{
		while (com->next != NULL)
			com = com->next;
		com->next = new;
	}
}

void	commands_delone(t_commands *command)
{
	int	i;

	i = -1;
	if (!command)
		return ;
	while (command->cmd[++i][0] != '\0')
		ft_allocfree((void *)&command->cmd[i]);
	ft_allocfree((void *)&command->cmd[i]);
	i = -1;
	while (command->redir[++i][0] != '\0')
		ft_allocfree((void *)&command->redir[i]);
	ft_allocfree((void *)&command->redir[i]);
	ft_allocfree((void *)&command);
}

void	commands_clear(t_commands **command)
{
	t_commands *com;
	t_commands *temp;

	com = *command;
	while (com)
	{
		temp = com->next;
		commands_delone(com);
		com = temp;
	}
}
