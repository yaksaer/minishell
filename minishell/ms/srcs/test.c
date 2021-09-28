#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
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
