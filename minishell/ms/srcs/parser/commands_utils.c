/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:44:37 by marvin            #+#    #+#             */
/*   Updated: 2021/10/04 01:15:07 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	void	*result;

	result = (void *)malloc(newsize);
	if (!result)
		return (NULL);
	ft_memset(result, 0, newsize);
	if (!ptr)
		return (result);
	result = ft_memcpy(result, ptr, oldsize);
	free(ptr);
	return (result);
}

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
