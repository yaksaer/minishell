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

	ft_bzero(&descrip, sizeof(t_descrip));
	init_fd(&descrip);
}
