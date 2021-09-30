#include "../include/minishell.h"

char 	**copy_env_to_mass(char **env)
{
	char 	**ret;
	int		i;

	i = 0;
	while (env[i])
		i++;
	ret = (char **) ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
			return (NULL);
	}
	return (ret);
}

t_dlink_list	*copy_env_to_list(char **env)
{
	t_dlink_list 	*res_list;
	int				i;

	res_list = ft_calloc(1, sizeof(t_dlink_list));
	if (!res_list)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		ft_dlist_push_back(res_list, env[i]);
		if (ft_strcmp(env[i], res_list->tail->data))
			return (NULL);
	}
	return (res_list);
}