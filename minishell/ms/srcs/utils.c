#include "../include/minishell.h"

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

char	*str_get_key(char *var)
{
	int		i;
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

char 	**copy_env_to_mass(t_dlink_list *env)
{
	char 	**ret;
	t_node	*tmp;
	int		i;

	ret = (char **) ft_calloc(env->size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	tmp = env->head;
	i = 0;
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->data);
		if (!ret[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	return (ret);
}

int		ft_mass_size(char **str)
{
	int 	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//char 	**copy_env_to_mass(char **env)
//{
//	char 	**ret;
//	int		i;
//
//	ret = (char **) ft_calloc(ft_mass_size(env) + 1, sizeof(char *));
//	if (!ret)
//		return (NULL);
//	i = 0;
//	while (env[i])
//	{
//		ret[i] = ft_strdup(tmp->data);
//		if (!ret[i])
//			return (NULL);
//		i++;
//		tmp = tmp->next;
//	}
//	return (ret);
//}

t_dlink_list	*copy_env_to_list(char **env)
{
	t_dlink_list 	*res_list;
	char			*buf;
	int				i;

	res_list = ft_calloc(1, sizeof(t_dlink_list));
	if (!res_list)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		buf = ft_strdup(env[i]);
		if (!buf)
			return (NULL);
		ft_dlist_push_back(res_list, buf);
		res_list->tail->position = i;
		if (ft_strcmp(env[i], res_list->tail->data))
			return (NULL);
	}
	return (res_list);
}