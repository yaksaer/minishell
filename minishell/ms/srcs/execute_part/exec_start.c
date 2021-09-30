#include "../../include/minishell.h"

int		ft_mass_size(char **str)
{
	int 	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void 	init_fd(t_descrip *descrip)
{
	descrip->def_int = dup(0);
	descrip->def_out = dup(1);
	descrip->fd_in = dup(descrip->def_int);
}

int 	is_my_command(t_main *main, t_commands *command)
{
	if (ft_strcmp(command->cmd[0], "echo")
		|| ft_strcmp(command->cmd[0], "env")
		|| ft_strcmp(command->cmd[0], "export")
		|| ft_strcmp(command->cmd[0], "unset")
		|| ft_strcmp(command->cmd[0], "pwd")
		|| ft_strcmp(command->cmd[0], "cd")
		|| ft_strcmp(command->cmd[0], "exit"))
		return (1);
	return (0);
}

int		exec_my_command(t_main *main, t_commands *command)
{

}

void 	exec_command(t_main *main, int i)
{
	if (!main->commands[i]->cmd)
		return ;
	else if (is_my_command(main, main->commands[i]))
	{
		exec_my_command(main, main->commands[i]);
	}

}

int 	get_command(char *str, t_main *main)
{
	t_descrip	descrip;
	t_commands	*tmp;
	int 		i;

	ft_bzero(&descrip, sizeof(t_descrip));
	init_fd(&descrip);
	main->commands[0]->cmd = ft_split(str, ' ');
	i = 0;
	while (i < 1)
	{
		exec_command(main, i);
		i++;
	}
}
