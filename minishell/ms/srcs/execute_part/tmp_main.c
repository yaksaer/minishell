#include "../../include/minishell.h"

//int	init_main(t_main *main, char **envp)
//{
//	main->sort_env = copy_env_to_list(envp);
//	if (!main->sort_env)
//		return (1);
//	sort_dlist(main->sort_env);
//	main->env = copy_env_to_mass(envp);
//	if (!main->env)
//		return (1);
////	main->commands = (t_commands *)ft_calloc(2, sizeof(t_commands *)); //
////	if (!main->commands)
////		return (1);
////	main->commands = (t_commands *)ft_calloc(1, sizeof(t_commands));
////	if (!main->commands)
////		return (1);
//	return (0);
//}

//int main(int argc, char **argv, char **envp)
//{
//	char		*str;
//	t_main		main;
//
//	main = *(t_main *)ft_calloc(1, sizeof(main));
//	if (init_main(&main, envp))
//		return (1);
//	while (1)
//	{
//		str = readline("minishell:");
//		get_command(str, &main);
//		free(str);
//		if (str[0] == 'q')
//			break;
//	}
//	return (0);
//}

