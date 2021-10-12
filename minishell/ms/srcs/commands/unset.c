#include "../../include/minishell.h"

char	**mass_unset(char **env, char *val)
{
	int		i;
	int		j;
	char	**ret;
	char	*tmp;

	ret = ft_calloc(ft_mass_size(env) - 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (env[j])
	{
		tmp = str_get_key(env[j]);
		if (!tmp)
			break ;
		if (ft_strcmp(tmp, val) == 0)
			free(env[j++]);
		if (env[j])
			ret[i++] = env[j++];
		free(tmp);
	}
	//ret[i] = "\0";
	free(env);
	return (ret);
}

void	list_unset(t_main *main, char *val)
{
	t_node	*tmp;
	char	*str;
	int		i;

	tmp = main->sort_env->head;
	i = 0;
	while (tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, val) == 0)
		{
			tmp = tmp->next;
			free(ft_dlist_del_n(main->sort_env, i));
			free(str);
			i++;
			continue ;
		}
		free(str);
		tmp = tmp->next;
		i++;
	}
}

int	find_key(t_main *main, char *val)
{
	t_node	*tmp;
	char	*str;

	tmp = main->sort_env->head;
	while (tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, val) == 0)
		{
			free(str);
			return (0);
		}
		free(str);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_unset(t_main *main, t_commands *command)
{
	int	i;

	if (ft_mass_size(command->cmd) > 1)
	{
		i = 0;
		while (command->cmd[++i])
		{
			if (check_key(command->cmd[i], "unset")
				|| find_key(main, command->cmd[i]))
				continue ;
			list_unset(main, command->cmd[i]);
			main->env = mass_unset(main->env, command->cmd[i]);
			if (!main->env)
				return (1);
		}
	}
	return (0);
}
