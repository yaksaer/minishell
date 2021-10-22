/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:19 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/22 16:59:56 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	add_pwd_env(t_main *main, char *str)
{
	char	*buf;

	if (main->vault_pwd)
		free(main->vault_pwd);
	if (str && find_key_node(main->sort_env, "PWD"))
	{
		buf = ft_strjoin("PWD=", str);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_list(main->sort_env, buf, "PWD");
		buf = ft_strdup(buf);
		if (!buf)
			error_n_exit(NULL, NULL, 1);
		add_to_unsort_list(main->unsort_env, buf, "PWD");
		main->vault_pwd = ft_strdup(buf);
	}
	else
		main->vault_pwd = ft_strjoinm("PWD=", ft_strdup(buf), 2);
	free(str);
}

void	change_env(t_main *main, char *old_dir, char *tmp)
{
	char	*buf;
	t_node	*nod;

	buf = getcwd(NULL, 0);
	nod = find_key_node(main->sort_env, "PWD");
	if (!buf && !nod)
		tmp = ft_strjoin(main->vault_pwd + 4, tmp);
	else if (!buf)
		tmp = ft_strjoin(find_key_node(main->sort_env, "PWD")->data + 4, tmp);
	else
		tmp = buf;
	add_pwd_env(main, tmp);
	if (find_key_node(main->unsort_env, "OLDPWD"))
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
