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

void	change_env(t_main *main, char *old_dir, char *tmp)
{
	add_pwd_env(main);
	if (!find_key_node(main->sort_env, "OLDPWD") && main->flag == 0)
	{
		main->flag += 1;
		tmp = ft_strjoin("OLDPWD=", old_dir);
		if (!tmp)
			error_n_exit(NULL, NULL, 1);
		add_to_list(main->sort_env, tmp, "OLDPWD");
		tmp = ft_strjoin("OLDPWD=", old_dir);
		if (!tmp)
			error_n_exit(NULL, NULL, 1);
		add_to_unsort_list(main->unsort_env, tmp, "OLDPWD");
	}
	else
	{
		tmp = ft_strjoin("OLDPWD=", old_dir);
		if (!tmp)
			error_n_exit(NULL, NULL, 1);
		add_to_list(main->sort_env, tmp, "OLDPWD");
		tmp = ft_strjoin("OLDPWD=", old_dir);
		if (!tmp)
			error_n_exit(NULL, NULL, 1);
		add_to_unsort_list(main->unsort_env, tmp, "OLDPWD");
	}
}

int	step_back(t_main *main)
{
	char	*curr_path;
	int		i;
	int		len;
	char	*tmp;

	if (!(curr_path = getcwd(NULL, 0))) //TODO: Нормальное сообщение об
		// ошибке и выход
		return (1);
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
	{
		free(tmp);
		change_env(main, curr_path, tmp);
	}
	free(curr_path);
	return (0);
}

int	go_home(t_main *main, t_node *node)
{
	char	*tmp;
	char	curr_path[1024];
	int		ret;

	ret = 0;
	if (!node)
	{
		printf("minishell: cd: HOME not set\n");
		return (0);
	}
	tmp = ft_strdup(node->data + 5);
	ft_bzero(curr_path, 1024);
	getcwd(curr_path, 1024);
	free(tmp);
	if (!chdir(tmp))
	{
		free(tmp);
		change_env(main, curr_path, tmp);
	}
	else
		ret += 1;
	return (ret);
}

int	go_home_start(t_main *main)
{
	t_node	*node;
	int		ret;
	char	*tmp;

	node = main->unsort_env->head;
	while (node)
	{
		tmp = get_env_key(node);
		if (ft_strcmp(tmp, "HOME") == 0)
		{
			free(tmp);
			break ;
		}
		free(tmp);
		node = node->next;
	}
	ret = go_home(main, node);
	if (ret == 1)
		printf("Minishell: cd: %s: No such file or directory\n",
			node->data + 5);
	return (ret);
}

int	ft_cd(t_main *main, t_commands *command)
{
	char	old_dir[1024];
	char	*tmp;

	ft_bzero(old_dir, FILENAME_MAX);
	getcwd(old_dir, FILENAME_MAX);
	if (ft_mass_size(command->cmd) == 1)
		return (go_home_start(main));
	else if (command->cmd[1][0] == '.' && command->cmd[1][1] == '.'
		&& (!command->cmd[1][2] || ft_isspace(command->cmd[1][2])))
		step_back(main);
	else if (command->cmd[1][0] == '.' && (!command->cmd[1][1] || ft_isspace
		(command->cmd[1][2])))
		change_env(main, old_dir, tmp);
	else
	{
		if (chdir(command->cmd[1]) < 0)
		{
			printf("Minishell: cd: %s: No such file or directory\n",
				command->cmd[1]);
			return (1);
		}
		else
			change_env(main, old_dir, tmp);
	}
	return (0);
}
