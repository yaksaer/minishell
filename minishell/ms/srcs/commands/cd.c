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
	add_pwd_env(main, tmp);
	if (!find_key_node(main->unsort_env, "OLDPWD") && main->flag == 0)
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

void	find_exist_path(t_main *main, char *tmp, char **buf)
{
	char	*dir;
	char	*str;
	int		i;

	dir = ft_strjoin("/", buf[0]);
	if (!dir)
		error_n_exit(NULL, (void **)buf, 1);
	i = 1;
	str = NULL;
	while (access(dir, F_OK) == 0)
	{
		if (str)
			free(str);
		str = dir;
		dir = ft_strjoinm(ft_strjoin(dir, "/"), buf[i++], 1);
		if (!dir)
			error_n_exit(NULL, (void **)buf, 1);
	}
	free(dir);
	chdir(str);
	change_env(main, tmp + 4, str);
	free(str);
}

int	cwd_error(t_main *main, char *new_dir)
{
	char	**buf;
	char	*str;
	t_node	*tmp;

	tmp = find_key_node(main->unsort_env, "PWD");
	if (!tmp)
		str = ft_strdup(main->vault_pwd);
	else
		str = ft_strdup(tmp->data);
	if (ft_strstr_count(str, "/..") == 1 && ft_strcmp(new_dir, "/..") == 0)
	{
		buf = ft_split(str + 4, '/');
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		find_exist_path(main, str, buf);
		free_dmass(buf);
		free(str);
		return (0);
	}
	if (ft_strstr_count(str, "/..") == 0 && ft_strstr_count(str, "/.") == 0)
		printf("cd: error retrieving current directory: getcwd: cannot access"
		   		"parent directories: No such file or directory\n");
	change_env(main, str + 4, new_dir);
	free(str);
	return (0);
}

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
