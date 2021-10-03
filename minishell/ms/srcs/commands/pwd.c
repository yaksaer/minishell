#include "../../include/minishell.h"

int		ft_pwd(void)
{
	char	path[10240];

	errno = 0;
	getcwd(path, 10240);
	if (errno)
		perror(NULL);
	else
		printf("%s\n", path);
	return (0);
}