#include "../../include/minishell.h"

int		check_key(char *val, char *prog)
{
	int 	i;
	int 	count;

	i = 0;
	count = 0;
	while (val[i] && val[i] != '=')
	{
		if (!ft_isalnum(val[i]) && val[i] != '_')
		{
			printf("minishell: %s: '%c': not a valid identifier\n",prog,
				   val[i]);
			return (1);
		}
		if (ft_isalpha(val[i]))
			count++;
		i++;
	}
	if (count == 0)
	{
		printf("minishell: %s: '%s': not a valid identifier\n", prog, val);
		return (1);
	}
	return (0);
}

int 	add_to_list(t_main *main, char *var, char *key)
{
	t_node		*tmp;
	int 		i;

	tmp = main->sort_env->head;
	var = add_quotes_util(var);
	if (!var)
		return (1);
	i = 0;
	while (++i && tmp)
	{
		if (ft_strcmp(get_env_key(tmp), key) > 0)
		{
			ft_dlist_insert(main->sort_env, i - 2, var);
			return (0);
		}
		else if (ft_strcmp(get_env_key(tmp), key) == 0)
		{
			ft_dlist_del_n(main->sort_env, i - 1);
			ft_dlist_insert(main->sort_env, i - 2, var);
			return (-1);
		}
		tmp = tmp->next;
	}
	ft_dlist_push_back(main->sort_env, var);
	return (0);
}

char	*str_get_key(char *var)
{
	int 	i;
	char	*ret;

	i = 0;
	while (var[i] != '=')
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (var[++i] != '=')
		ret[i] = var[i];
	ret[i] = '\0';
	return (ret);
}

char	**realloc_n_add(char **src, char *var)
{
	int		i;
	char 	**ret;

	i = 0;
	while (src[i])
		i++;
	ret = ft_calloc(i + 2, sizeof(char*));
	if (!ret)
		return (NULL);
	i = -1;
	while (src[++i])
		ret[i] = src[i];
	ret[i++] = ft_strdup(var);
	ret[i] = '\0';
	free(src);
	return (ret);
}

int		replace_value(char **src, char *var)
{
	int		i;
	char	*ret;

	i = -1;
	while (src[++i])
	{
		if (ft_strcmp(str_get_key(src[i]), str_get_key(var)) == 0)
		{
			free(src[i]);
			ret = ft_calloc(ft_strlen(var) + 1, sizeof(char));
			if (!ret)
				;
			ret = ft_strcpy(ret, var);
			src[i] = ret;
		}
	}
}

int		start_export(t_main *main, t_commands *command)
{
	int 	i;
	int 	flag;
	char	*str;

	i = 0;
	flag = 0;
	while (command->cmd[++i])
	{
		flag += check_key(command->cmd[i], "export");
		if (flag)
			continue;
		str = str_get_key(command->cmd[i]);
		if (!str)
			return (1);
		if (add_to_list(main, command->cmd[i], str) < 0)
			replace_value(main->env, command->cmd[i]);
		else
			main->env = realloc_n_add(main->env, command->cmd[i]);
		if (!main->env)
			return (1);
		free(str);
	}
	return (flag);
}

int		ft_export(t_main *main, t_commands *command)
{
	t_node	*tmp;
	int		ret;

	tmp = main->sort_env->head;
	if (ft_mass_size(command->cmd) > 1)
		ret = start_export(main, command);
	else
	{
		while (tmp)
		{
			printf("declare -x %s\n", tmp->data);
			tmp = tmp->next;
		}
	}
	if (ret > 0)
		return (1);
	return (0);
}

