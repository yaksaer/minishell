#include "../../include/minishell.h"

int	ft_env(t_main *main)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = main->sort_env->head;
	while (i < main->sort_env->size)
	{
		if (!tmp)
			tmp = main->sort_env->head;
		if (tmp->position == i)
		{
			printf("%s\n", tmp->data);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
