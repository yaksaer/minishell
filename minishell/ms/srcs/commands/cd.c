#include "../../include/minishell.h"

void	change_env(t_main *main, char *old_dir)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_dir);
	if (!tmp)
		;
	add_to_list(main->sort_env, tmp, "OLDPWD");
	replace_value(main->env, tmp);
	tmp = getcwd(NULL, 0);
	tmp = ft_strjoinm("PWD=", tmp, 2);
	if (!tmp)
		;
	add_to_list(main, tmp, "PWD");
	replace_value(main->env, tmp);
}

int	step_back(t_main *main)
{
	char	*curr_path;
	int		i;
	int		len;
	char	*tmp;

	curr_path = getcwd(NULL, 0);
	len = ft_strlen(curr_path) - ft_strlen(ft_strrchr(curr_path, '/'));
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
	free(curr_path);
	free(tmp);
	return (0);
}

int	go_home(t_main *main)
{
	int		i;
	char	*str;
	char	*tmp;
	char	curr_path[1024];

	i = -1;
	ft_bzero(curr_path, 1024);
	getcwd(curr_path, 1024);
	while (main->env[++i])
	{
		tmp = str_get_key(main->env[i]);
		if (ft_strcmp(tmp, "HOME") == 0)
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	if (!main->env[i])
		return (printf("minishell: cd: HOME not set\n"));
	str = ft_strdup(main->env[i] + 5);
	if (!chdir(str))
		change_env(main, curr_path);
	free(str);
	return (0);
}

int	ft_cd(t_main *main, t_commands *command)
{
	char	*old_dir;

	if (ft_mass_size(command->cmd) == 1)
		return (go_home(main));
	else if (command->cmd[1][0] == '.' && command->cmd[1][1] == '.'
		&& (!command->cmd[1][2] || ft_isspace(command->cmd[1][2])))
		step_back(main);
	else if (command->cmd[1][0] == '.' && !command->cmd[1][1])
		return (0);
	else
	{
		old_dir = getcwd(NULL, 0);
		if (chdir(command->cmd[1]) < 0)
		{
			printf("Minishell: cd: %s: No such file or directory\n",
				   command->cmd[1]);
			return (1);
		}
		else
		{
			change_env(main, old_dir);
			free(old_dir);
		}
	}
	return (0);
}
