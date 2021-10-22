/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:44:37 by marvin            #+#    #+#             */
/*   Updated: 2021/10/22 19:49:11 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**add_string_to_massive(char ***dest, char **src, int number)
{
	char	**result;
	char	**tmp;
	char	*temp;
	int		i;

	i = 0;
	tmp = *dest;
	temp = *src;
	result = (char **)ft_calloc(number + 2, sizeof(char *));
	if (!result)
		return (NULL);
	while (tmp && tmp[i])
	{	
		result[i] = ft_strdup(tmp[i]);
		ft_allocfree((void *)&tmp[i++]);
	}
	result[i] = ft_strdup(temp);
	ft_allocfree((void *)&temp);
	ft_allocfree((void *)&tmp);
	*dest = tmp;
	*src = temp;
	return (result);
}

t_commands	*commands_new(char **cmd, char **redir, int input, int output)
{
	t_commands	*new;

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
	t_commands	*com;

	com = *command;
	if (!new)
		return ;
	if (!*command)
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
	if (command->cmd)
	{
		while (command->cmd[++i] != NULL)
			ft_allocfree((void *)&command->cmd[i]);
		free(command->cmd[i]);
		free(command->cmd);
	}
	i = -1;
	if (command->redir)
	{
		while (command->redir[++i] != NULL)
			ft_allocfree((void *)&command->redir[i]);
		free(command->redir[i]);
		free(command->redir);
	}
	command->next = NULL;
}

void	commands_clear(t_commands **command)
{
	t_commands	*com;
	t_commands	*temp;

	com = *command;
	while (com)
	{
		temp = com->next;
		if (com->input)
			close(com->input);
		if (com->output)
			close(com->output);
		commands_delone(com);
		ft_allocfree((void *)&com);
		com = temp;
	}
	*command = NULL;
}
