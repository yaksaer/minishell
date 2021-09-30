#include "../../include/minishell.h"

//static int	tmp_init_main(t_main *main, char **envp)
//{
//	t_commands	*commands;
//
//	main = (t_main *)ft_calloc(1, sizeof(&main));
//	if (!main)
//		return (1);
//	commands = (t_commands *)ft_calloc(1, sizeof(t_commands));
//	main->commands = &commands;
//	 main->sort_env = copy_env_to_list(envp); //need to sort this list
//	 if (!main->sort_env)
//	 	return (1);
//	 main->env = copy_env_to_mass(envp);
//	 if (!main->env)
//	 	return (1);
//	return (0);
//}

int main(int argc, char **argv, char **envp)
{
	char		*str;
	t_main		main;

	main = *(t_main *)ft_calloc(1, sizeof(main));
	if (init_main(&main, envp))
		return (1);
	while (1)
	{
		str = readline("minishell:");
		get_command(str, &main);
		free(str);
		if (str[0] == 'q')
			break;
	}
	return (0);
}

