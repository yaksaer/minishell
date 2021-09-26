#include "../minishell.h"

void	free_commands(t_command **cmds)
{
	t_command *tmp;
	t_command *list;

	tmp = NULL;
	list = *cmds;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list->str);
		free(list);
		list = tmp;
	}
	*cmds = NULL;
}
