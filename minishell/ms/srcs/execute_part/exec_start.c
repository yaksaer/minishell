#include "../../include/minishell.h"

void 	init_fd(t_descrip *descrip)
{
	descrip->def_int = dup(0);
	descrip->def_out = dup(1);
	descrip->fd_in = dup(descrip->def_int);
}

int 	get_command(char *str, char **envp)
{
	t_descrip	descrip;
	t_commands	*tmp;

	ft_bzero(&descrip, sizeof(t_descrip));
	init_fd(&descrip);
}

int tmp_main(int argc, char **argv, char **envp)
{
	char *str;

	while (1)
	{
		str = readline("minishell:");
		free(str);
		if (str[0] == 'q')
		{
			free(str);
			str = malloc(1);
			exit (0);
		}
	}
	return (0);
}
