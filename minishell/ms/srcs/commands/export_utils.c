/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:41 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:42 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_export(t_dlink_list *env)
{
	t_node	*tmp;
	int		i;
	size_t	flag;

	tmp = env->head;
	while (tmp)
	{
		i = 0;
		flag = 0;
		ft_putstr_fd("declare -x ", 1);
		while (tmp->data[i])
		{
			if (tmp->data[i] == '=')
			{
				ft_putchar_fd(tmp->data[i++], 1);
				flag += write(1, "\"", 1);
			}
			if (tmp->data[i])
				ft_putchar_fd(tmp->data[i++], 1);
		}
		if (flag > 0)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

int	add_to_unsort_list(t_dlink_list *env, char *cmd, char *key)
{
	t_node	*tmp;
	char	*str;
	int		i;

	tmp = env->head;
	i = 0;
	while (++i && tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, key) == 0)
		{
			free(ft_dlist_del_n(env, i - 1));
			ft_dlist_insert(env, i - 2, cmd);
			free(str);
			return (0);
		}
		free(str);
		tmp = tmp->next;
	}
	ft_dlist_push_back(env, cmd);
	return (1);
}

int	unsort_list_proc(char *comnd, t_dlink_list *env)
{
	char	*str;
	char	*cmd;

	str = str_get_key(comnd);
	if (!str)
		error_n_exit(NULL, NULL, 1);
	cmd = ft_strdup(comnd);
	if (!cmd)
		error_n_exit(str, NULL, 1);
	add_to_unsort_list(env, cmd, str);
	free(str);
	return (0);
}
