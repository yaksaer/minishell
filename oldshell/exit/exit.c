#include "../minishell.h"

void exit_from_minishell(t_mainstruct *main)
{
	ft_putendl("exit");
	if (!main->cmds->next)
	{
		main->exit = true;
		main->exit_code = EXIT_SUCCESS;
	}
	else if (main->cmds->next && main->cmds->next->str)
	{
		if (!str_is_numeric(main->cmds->next->str))
		{
			main->exit = true;
			main->exit_code = EXIT_NOT_NUMERIC;
			ft_putstr_fd("21sh: exit: ", STDERR_FILENO);
			ft_putstr_fd(main->cmds->next->str, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		}
		else if (main->cmds->next->next && main->cmds->next->next->str)
		{
			main->exit = false;
			main->exit_code = EXIT_FAILURE;
			ft_putendl_fd("21sh: exit: too many arguments", STDERR_FILENO);
		}
		else if (str_is_numeric(main->cmds->next->str) && !main->cmds->next->next)
		{
			main->exit = true;
			main->exit_code = (unsigned char)ft_atoi(main->cmds->next->str);
		}
	}
}

