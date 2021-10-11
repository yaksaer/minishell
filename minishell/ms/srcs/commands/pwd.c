#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	path[1024];

	ft_bzero(path, 1024);
	if (getcwd(path, 1024) == NULL)
		return (1);
	printf("%s\n", path);
	return (0);
}
