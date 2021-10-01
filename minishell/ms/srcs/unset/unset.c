#include "../../include/minishell.h"

char 	**mass_unset(char **env, char *val)
{
	int		i;
	int 	j;
	char	**ret;

	ret = ft_calloc(ft_mass_size(env) - 1, sizeof(char*));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (env[j])
	{
		if (ft_strcmp(str_get_key(env[i]), val) == 0)
			j++;
		if (env[j])
			ret[i++] = env[j++];
	}
	ret[i] = '\0';
	free(env);
	return (ret);
}

void 	list_unset(t_main *main, char *val)
{
	t_node	*tmp;
	int 	i;

	tmp = main->sort_env->head;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(get_env_key(tmp), val) == 0)
			ft_dlist_del_n(main->sort_env, i);
		tmp = tmp->next;
		i++;
	}
}

int 	find_key(t_main *main, char *val)
{
	t_node	*tmp;

	tmp = main->sort_env->head;
	while (tmp)
	{
		if (ft_strcmp(get_env_key(tmp), val) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		ft_unset(t_main *main, t_commands *command)
{
	int 	i;

	if (ft_mass_size(command->cmd) > 1)
	{
		i = 0;
		while (command->cmd[++i])
		{
			if (check_key(command->cmd[i], "unset")
				|| find_key(main, command->cmd[i]))
				continue;
			list_unset(main, command->cmd[i]);
			main->env = mass_unset(main->env, command->cmd[i]);
			if (!main->env)
				return (1);
		}
	}
	return (0);
}