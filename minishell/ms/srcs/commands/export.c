#include "../../include/minishell.h"

int	check_key(char *val, char *prog)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (val[i] && val[i] != '=')
	{
		if (!ft_isalnum(val[i]) && val[i] != '_')
		{
			printf("minishell: %s: '%c': not a valid identifier\n", prog,
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

void	ft_dlist_insert_head(t_dlink_list *list, size_t index, char *data)
{
	t_node	*elm;
	t_node	*ins;

	elm = NULL;
	ins = NULL;
	elm = ft_dlist_get_n(list, index);
	if (elm == NULL)
		return ;
	ins = (t_node *)malloc(sizeof(t_node));
	if (ins == NULL)
		return ;
	ins->data = data;
	ins->prev = NULL;
	ins->next = elm;
	list->head = ins;
	elm->prev = ins;
	if (!elm->next)
		list->tail = elm;
	list->size++;
}

int	add_to_list(t_main *main, char *cmd, char *key)
{
	t_node	*tmp;
	char	*var;
	char	*str;
	int		i;

	tmp = main->sort_env->head;
	var = add_quotes_util(cmd);
	if (!var)
		return (1);
	i = 0;
	while (++i && tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, key) > 0)
		{
			if (tmp == main->sort_env->head)
				ft_dlist_insert_head(main->sort_env, 0, var);
			else
				ft_dlist_insert(main->sort_env, i - 2, var);
			free(str);
			return (0);
		}
		else if (ft_strcmp(str, key) == 0)
		{
			free(ft_dlist_del_n(main->sort_env, i - 1));
			ft_dlist_insert(main->sort_env, i - 2, var);
			free(str);
			return (-1);
		}
		free(str);
		tmp = tmp->next;
	}
	ft_dlist_push_back(main->sort_env, var);
	return (0);
}

char	*str_get_key(char *var)
{
	int		i;
	char	*ret;

	i = 0;
	if (!var)
		return (NULL);
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
	char	**ret;

	i = 0;
	while (src[i])
		i++;
	ret = ft_calloc(i + 2, sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (src[++i])
		ret[i] = src[i];
	ret[i++] = ft_strdup(var);
	if (!ret[i - 1])
		return (NULL);
//	ret[i] = "\0";
	free(src);
	return (ret);
}

int	replace_value(char **src, char *var)
{
	int		i;
	char	*ret;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	tmp1 = str_get_key(var);
	while (src[++i])
	{
		tmp2 = str_get_key(src[i]);
		if (ft_strcmp(tmp2, tmp1) == 0)
		{
			free(src[i]);
			ret = ft_calloc(ft_strlen(var) + 1, sizeof(char));
			if (!ret)
				return (1);
			ret = ft_strcpy(ret, var);
			src[i] = ret;
			free(tmp2);
			break ;
		}
		free(tmp2);
	}
	free(tmp1);
	return (0);
}

int	start_export(t_main *main, t_commands *command)
{
	int		i;
	int		flag;
	char	*str;

	i = 0;
	flag = 0;
	while (command->cmd[++i])
	{
		flag += check_key(command->cmd[i], "export");
		if (flag)
			continue ;
		str = str_get_key(command->cmd[i]);
		if (!str)
			return (1);
		if (add_to_list(main, command->cmd[i], str) < 0)
		{
			if (replace_value(main->env, command->cmd[i]))
			{
				free(str);
				return (1);
			}
		}
		else
			main->env = realloc_n_add(main->env, command->cmd[i]);
		free(str);
		if (!main->env)
			return (1);
	}
	return (flag);
}

int	ft_export(t_main *main, t_commands *command)
{
	t_node	*tmp;
	int		ret;

	tmp = main->sort_env->head;
	ret = 0;
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
