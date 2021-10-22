/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:56:18 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:56:58 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_n_exit(void *buf, void **buf2, int flag)
{
	if (flag == 1)
		printf("Minishell: malloc error\n");
	free_all(buf, buf2);
	exit(1);
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
	while (var[i] && var[i] != '=')
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (var[++i] != '=' && var[i])
		ret[i] = var[i];
	ret[i] = '\0';
	return (ret);
}

char	**copy_env_to_mass(t_dlink_list *env)
{
	char	**ret;
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

t_dlink_list	*copy_env_to_list(char **env)
{
	t_dlink_list	*res_list;
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
		if (ft_strcmp(env[i], res_list->tail->data))
			return (NULL);
	}
	return (res_list);
}
