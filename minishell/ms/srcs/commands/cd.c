#include "../../include/minishell.h"

void		change_env(t_main *main, char *old_dir)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_dir);
	if (!tmp)
		;
	add_to_list(main, tmp, "OLDPWD");
	replace_value(main->env, tmp);
	free(tmp);
	tmp = getcwd(NULL, 0);
	tmp = ft_strjoinm("PWD=", tmp, 2);
	if (!tmp)
		;
	add_to_list(main, tmp, "PWD");
	replace_value(main->env, tmp);
}

int		step_back(t_main *main, t_commands *command)
{
	char	*curr_path;
	int		i;
	int		len;
	char	*tmp;

	curr_path = getcwd(NULL, 0);
	len = ft_strlen(curr_path) - ft_strlen( ft_strrchr(curr_path, '/'));
	tmp = ft_calloc(len + 2, sizeof(char));
	if (!tmp)
		return (1);
	i = -1;
	if (len == 0)
		tmp[0] = '/';
	else
		while (++i < len)
			tmp[i] = curr_path[i];
	if (!chdir(tmp))
		change_env(main, curr_path);
	curr_path = getcwd(NULL, 0);
	free(curr_path);
	free(tmp);
	return (0);
}

int		ft_cd(t_main *main, t_commands *command)
{
	char	*old_dir;

	if (command->cmd[1][0] == '.' && command->cmd[1][1] == '.'
		&& !command->cmd[1][2])
		step_back(main, command);
	else if (command->cmd[1][0] == '.' && !command->cmd[1][1])
		return (0);
	else
	{
		old_dir = getcwd(NULL, 0);
		if (chdir(command->cmd[1]) < 0)
			printf("Minishell: cd: %s: No such file or directory\n",
				   command->cmd[1]);
		else
		{
			change_env(main, old_dir);
			free(old_dir);
		}
	}
}