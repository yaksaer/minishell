/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:49:00 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:49:01 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_my_command(t_commands *command)
{
	if (!ft_strcmp(command->cmd[0], "echo")
		|| !ft_strcmp(command->cmd[0], "env")
		|| !ft_strcmp(command->cmd[0], "export")
		|| !ft_strcmp(command->cmd[0], "unset")
		|| !ft_strcmp(command->cmd[0], "pwd")
		|| !ft_strcmp(command->cmd[0], "cd")
		|| !ft_strcmp(command->cmd[0], "exit"))
		return (1);
	return (0);
}

char	*get_env_key(t_node *node)
{
	int		i;
	char	*ret;

	i = 0;
	if (!node)
		return (NULL);
	while (node->data[i] && node->data[i] != '=')
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, node->data, i + 1);
	return (ret);
}

void	swap_dlist_nodes(t_node *curr, t_node *second, t_dlink_list *dlist)
{
	if (curr == dlist->head)
		dlist->head = second;
	if (second == dlist->tail)
		dlist->tail = curr;
	if (curr->prev)
		curr->prev->next = second;
	second->prev = curr->prev;
	if (second->next)
		second->next->prev = curr;
	curr->next = second->next;
	second->next = curr;
	curr->prev = second;
}

int	is_dlist_sort(t_dlink_list *dlist)
{
	t_node	*tmp_node;
	char	*tmp;
	char	*tmp2;
	int		flag;

	tmp_node = dlist->head;
	flag = 0;
	while (tmp_node)
	{
		tmp = get_env_key(tmp_node);
		if (!tmp)
			break ;
		tmp2 = get_env_key(tmp_node->next);
		if (!tmp2)
			break ;
		if (ft_strcmp(tmp, tmp2) > 0)
			flag += 1;
		ft_allocfree((void *)&tmp);
		ft_allocfree((void *)&tmp2);
		tmp_node = tmp_node->next;
	}
	ft_allocfree((void *)&tmp);
	ft_allocfree((void *)&tmp2);
	return (flag);
}

int	sort_dlist(t_dlink_list *dlist)
{
	char	*tmp;
	char	*tmp2;
	t_node	*tnode;

	while (is_dlist_sort(dlist))
	{
		tnode = dlist->head;
		while (tnode)
		{
			tmp = get_env_key(tnode);
			if (!tmp)
				break ;
			tmp2 = get_env_key(tnode->next);
			if (!tmp2)
				break ;
			if (ft_strcmp(tmp, tmp2) > 0)
				swap_dlist_nodes(tnode, tnode->next, dlist);
			tnode = tnode->next;
			ft_allocfree((void *)&tmp);
			ft_allocfree((void *)&tmp2);
		}
		ft_allocfree((void *)&tmp);
		ft_allocfree((void *)&tmp2);
	}
	return (0);
}
