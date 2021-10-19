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
		return (1);
	cmd = ft_strdup(comnd);
	if (!cmd)
		return (1);
	add_to_unsort_list(env, cmd, str);
	return (0);
}
