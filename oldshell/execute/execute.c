#include "../minishell.h"

void	split_var_path(t_mainstruct *main)
{
		char	*value;
		char	**path_values;
		DIR 	*dir;
		struct	dirent *include;
		int		i;
		bool	found;

		found = false;
		value = get_env_value("PATH", main->env_list);
		path_values = ft_split(value, ':');
		free_n_null_ptr((void **) &value);
		i = 0;
		dir = opendir(path_values[i]);
		while (dir && !found)
		{
			include = readdir(dir);
//			if ()
			while (include)
			{

				include = readdir(dir);
			}
			i++;
			dir = opendir(path_values[i]);
		}




}

void	find_bin_path(t_mainstruct *main)
{
	split_var_path(main);
}

void	exec_commands(t_mainstruct *main)
{
	if (main->cmds && main->cmds->type == CMD)
	{
		if (!ft_strcmp(main->cmds->str, "exit"))
			exit_from_minishell(main);
		else
		{
//			g_signal.si_pid = fork();
//			if (g_signal.si_pid == 0)
			{
				find_bin_path(main);
//				main->dir = opendir("whereis");
//				if (1 == 1)
//					;
			}
		}
	}
}