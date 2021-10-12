#include "../../include/minishell.h"

int	ft_echo(int argc, char **argv)
{
	bool	n_option;
	int		i;

	n_option = false;
	if (argc == 1)
		printf("\n");
	i = 1;
	if (argc >= 2 && ft_strlen(argv[1]) == 2
		&& !ft_strncmp(argv[1], "-n", 2))
	{
		n_option = true;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		i++;
		if (i == argc && !n_option)
			printf("\n");
		else if (i < argc)
			printf(" ");
	}
	return (0);
}
