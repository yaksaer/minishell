#include "../minishell.h"

int		main(int argc, char **argv, char **env)
{
	int 	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}

