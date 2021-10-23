/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:50 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	list_unset(t_dlink_list *env, char *val)
{
	t_node	*tmp;
	char	*str;
	int		i;

	tmp = find_key_node(env, val);
	if (!tmp)
		return ;
	tmp = env->head;
	i = 0;
	while (tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, val) == 0)
		{
			tmp = tmp->next;
			free(ft_dlist_del_n(env, i));
			free(str);
			i++;
			continue ;
		}
		free(str);
		tmp = tmp->next;
		i++;
	}
}

int	ft_unset(t_main *main, t_commands *command)
{
	int	i;
	int	ret;

	ret = 0;
	if (ft_mass_size(command->cmd) > 1)
	{
		i = 0;
		while (command->cmd[++i])
		{
			if (ft_strchr(command->cmd[i], '='))
			{
				printf("minishell: unset: '%s': not a valid identifier\n",
					command->cmd[i]);
				ret = 1;
				continue ;
			}
			if (check_key(command->cmd[i], "unset") > 0)
				ret = 1;
			list_unset(main->sort_env, command->cmd[i]);
			list_unset(main->unsort_env, command->cmd[i]);
		}
	}
	return (ret);
}
