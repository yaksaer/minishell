#include "../../include/minishell.h"

static int	replace_in_list(t_dlink_list *env, int n, char *cmd, char **str)
{
	char	*buf;

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
	int		flag;
	char	*str;
	char	*cmd;

	i = 0;
	flag = 0;
	while (command->cmd[++i])
	{
		flag = check_key(command->cmd[i], "export");
		if (flag > 0)
			continue ;
		str = str_get_key(command->cmd[i]);
		if (!str)
			return (1);
		cmd = ft_strdup(command->cmd[i]);
		if (!cmd)
			return (1);
		add_to_list(main->sort_env, cmd, str);
		if (flag == -1)
			if (unsort_list_proc(command->cmd[i], main->unsort_env))
				return (1);
		free(str);
	}
	return (flag);
}

int	ft_export(t_main *main, t_commands *command)
{
	int		ret;

	ret = 0;
	if (ft_mass_size(command->cmd) > 1)
		start_export(main, command);
	else
		print_export(main->sort_env);
	if (ret > 0)
		return (1);
	return (0);
}
