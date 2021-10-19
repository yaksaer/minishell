#include "../../include/minishell.h"

int	ft_env(t_main *main)
{
	t_node	*tmp;

	tmp = main->unsort_env->head;
	while (tmp)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}
