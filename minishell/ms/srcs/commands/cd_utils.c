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

t_node	*find_key_node(t_dlink_list *env, char *key)
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
			return (tmp);
		}
		free(str);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_pwd_env(t_main *main, char *str)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		str = ft_strjoin(find_key_node(main->sort_env, "PWD")->data + 4, str);
	else
		str = buf;
	if (str)
	{
		buf = ft_strjoin("PWD=", str);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_list(main->sort_env, buf, "PWD");
		buf = ft_strdup(buf);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_unsort_list(main->unsort_env, buf, "PWD");
		if (main->vault_pwd)
			free(main->vault_pwd);
		main->vault_pwd = ft_strdup(buf);
	}
	else
		main->vault_pwd = ft_strjoinm("PWD=", ft_strdup(buf), 2);
	free(str);
}
