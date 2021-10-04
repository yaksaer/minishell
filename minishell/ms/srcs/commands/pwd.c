#include "../../include/minishell.h"

int		ft_pwd(void)
{
	char	*path;

	errno = 0;
	path = getcwd(NULL, 1);
	if (errno)
		perror(NULL);
	else
		printf("%s\n", path);
	free(path);
	return (0);
}
