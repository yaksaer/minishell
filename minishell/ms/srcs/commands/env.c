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
			if (ft_strchr(tmp->data, '=') != NULL)
				printf("%s\n", tmp->data);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
//TODO: Если убрать переменную то не печатает до конца; Если убрать и
// добавить такую же как и была - ??
