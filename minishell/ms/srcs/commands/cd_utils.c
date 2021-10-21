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

t_node	*find_key_node(t_dlink_list *env, char *key)
{
	t_node	*tmp;
	char	*str;

	tmp = env->head;
	while (tmp)
	{
		str = get_env_key(tmp);
		if (ft_strcmp(str, key) == 0)
		{
			free(str);
			return (tmp);
		}
		free(str);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_pwd_env(t_main *main, char *str)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		str = ft_strjoin(find_key_node(main->sort_env, "PWD")->data + 4, str);
	else
		str = buf;
	if (str)
	{
		buf = ft_strjoin("PWD=", str);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_list(main->sort_env, buf, "PWD");
		buf = ft_strdup(buf);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_unsort_list(main->unsort_env, buf, "PWD");
		if (main->vault_pwd)
			free(main->vault_pwd);
		main->vault_pwd = ft_strdup(buf);
	}
	else
		main->vault_pwd = ft_strjoinm("PWD=", ft_strdup(buf), 2);
	free(str);
}

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
