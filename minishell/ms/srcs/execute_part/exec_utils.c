#include "../../include/minishell.h"

void	free_dmass(char **str)
{
	int		i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}

void	wait_child(t_main *main)
{
	int		stat;
	int		ret;

	ret = 0;
	if (main->pid != 0)
	{
		waitpid(main->pid, &stat, 0);
		if (WIFEXITED(stat))
			ret = WEXITSTATUS(stat);
		main->exit_code = ret;
	}
}
