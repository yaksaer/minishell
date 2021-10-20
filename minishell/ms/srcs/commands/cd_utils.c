/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:19 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 17:21:49 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_key_node(t_dlink_list *env, char *key)
{
	t_node	*tmp;
	char	*str;

	tmp = env->head;
	while (tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, key) == 0)
		{
			free(str);
			return (1);
		}
		free(str);
		tmp = tmp->next;
	}
	return (0);
}

void	add_pwd_env(t_main *main)
{
	char	*buf;

	if (find_key_node(main->sort_env, "PWD"))
	{
		buf = getcwd(NULL, 0);
		buf = ft_strjoinm("PWD=", buf, 2);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_list(main->sort_env, buf, "PWD");
		buf = getcwd(NULL, 0);
		buf = ft_strjoinm("PWD=", buf, 2);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_unsort_list(main->unsort_env, buf, "PWD");
	}
}
