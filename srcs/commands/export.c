/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:44 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:45 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	replace_in_list(t_dlink_list *env, int n, char *cmd, char **str)
{
	char	*buf;

	if (g_main->flag == 0)
	{
		free(cmd);
		free(*str);
		return (0);
	}
	free(ft_dlist_del_n(env, n - 1));
	buf = str_get_key(env->head->data);
	if (ft_strcmp(*str, buf) < 0)
		ft_dlist_insert_head(env, 0, cmd);
	else
		ft_dlist_insert(env, n - 2, cmd);
	free(buf);
	buf = str_get_key(env->tail->data);
	free(buf);
	free(*str);
	return (0);
}

static void	push_to_list(t_dlink_list *env, int n, char *cmd, t_node *tmp)
{
	if (tmp == env->head)
		ft_dlist_insert_head(env, 0, cmd);
	else
		ft_dlist_insert(env, n - 2, cmd);
}

int	add_to_list(t_dlink_list *env, char *cmd, char *key)
{
	t_node	*tmp;
	char	*str;
	int		i;

	tmp = env->head;
	i = 0;
	while (++i && tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, key) > 0)
		{
			push_to_list(env, i, cmd, tmp);
			free(str);
			return (1);
		}
		else if (ft_strcmp(str, key) == 0)
			return (replace_in_list(env, i, cmd, &str));
		free(str);
		tmp = tmp->next;
	}
	ft_dlist_push_back(env, cmd);
	return (0);
}

static int	start_export(t_main *main, t_commands *command)
{
	int		i;
	char	*str;
	char	*cmd;

	i = 0;
	main->flag = 0;
	while (command->cmd[++i])
	{
		main->flag = check_key(command->cmd[i], "export");
		if (main->flag > 0)
			continue ;
		str = str_get_key(command->cmd[i]);
		if (!str)
			error_n_exit(NULL, NULL, 1);
		cmd = ft_strdup(command->cmd[i]);
		if (!cmd)
			error_n_exit(str, NULL, 1);
		add_to_list(main->sort_env, cmd, str);
		if (main->flag == -1)
			unsort_list_proc(command->cmd[i], main->unsort_env);
		free(str);
	}
	return (main->flag);
}

int	ft_export(t_main *main, t_commands *command)
{
	int		ret;

	ret = 0;
	if (ft_mass_size(command->cmd) > 1)
		ret = start_export(main, command);
	else
		print_export(main->sort_env);
	if (ret > 0)
		return (1);
	return (0);
}
