#include "../../include/minishell.h"

int		ft_exit(t_main *main, t_commands *commands)
{
	int 	i;

	if (ft_mass_size(commands->cmd) > 2)
		printf("minishell: exit: too many arguments\n");
	else if (ft_mass_size(commands->cmd) == 1)
		exit(0);
	else
	{
		i = -1;
		while (commands->cmd[1][++i])
		{
			if (!ft_isdigit(commands->cmd[1][i]))
			{
				printf("bash: exit: %s: numeric argument required\n",
					   commands->cmd[1]);
				exit (255);
			}
		}
		exit (ft_atoi(commands->cmd[1]));
	}
}