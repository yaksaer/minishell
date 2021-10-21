/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:19 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 17:21:49 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	step_back(t_main *main)
{
	char	*curr_path;
	int		i;
	int		len;
	char	*tmp;

	curr_path = getcwd(NULL, 0);
	if (!curr_path)
		return (cwd_error(main, "/.."));
	len = ft_strlen(curr_path) - ft_strlen(ft_strrchr(curr_path, '/'));
	tmp = ft_calloc(len + 2, sizeof(char));
	if (!tmp)
		error_n_exit(NULL, NULL, 1);
	i = -1;
	if (len == 0)
		tmp[0] = '/';
	else
		while (++i < len)
			tmp[i] = curr_path[i];
	if (!chdir(tmp))
		change_env(main, curr_path, tmp);
	free(tmp);
	free(curr_path);
	return (0);
}

int	go_home(t_main *main, t_node *node)
{
	char	*tmp;
	char	curr_path[1024];
	int		ret;

	ret = 0;
	tmp = ft_strdup(node->data + 5);
	ft_bzero(curr_path, 1024);
	getcwd(curr_path, 1024);
	if (!chdir(tmp))
		change_env(main, curr_path, tmp);
	else
		ret += 1;
	return (ret);
}

int	go_home_start(t_main *main)
{
	t_node	*node;
	int		ret;

	node = find_key_node(main->sort_env, "HOME");
	if (!node)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	ret = go_home(main, node);
	if (ret == 1)
		printf("Minishell: cd: %s: No such file or directory\n",
			node->data + 5);
	return (ret);
}

void	one_dot_proc(t_main *main, char *old_dir, char *command)
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (!curr_path)
		cwd_error(main, "/.");
	else
		change_env(main, old_dir, command);
	free(curr_path);
}

int	ft_cd(t_main *main, t_commands *command)
{
	char	old_dir[1024];

	ft_bzero(old_dir, FILENAME_MAX);
	getcwd(old_dir, FILENAME_MAX);
	if (ft_mass_size(command->cmd) == 1)
		return (go_home_start(main));
	else if (command->cmd[1][0] == '.' && command->cmd[1][1] == '.'
		&& (!command->cmd[1][2] || ft_isspace(command->cmd[1][2])))
		step_back(main);
	else if (command->cmd[1][0] == '.' && (!command->cmd[1][1] || ft_isspace
		(command->cmd[1][2])))
		one_dot_proc(main, old_dir, command->cmd[1]);
	else
	{
		if (chdir(command->cmd[1]) < 0)
		{
			printf("Minishell: cd: %s: No such file or directory\n",
				command->cmd[1]);
			return (1);
		}
		else
			change_env(main, old_dir, command->cmd[1]);
	}
	return (0);
}
