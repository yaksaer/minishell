/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:56 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:57 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_my_command(t_main *main, t_commands *command)
{
	if (!ft_strcmp(command->cmd[0], "echo"))
		main->exit_code = ft_echo(ft_mass_size(command->cmd), command->cmd);
	else if (!ft_strcmp(command->cmd[0], "env"))
		main->exit_code = ft_env(main);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		main->exit_code = ft_pwd();
	else if (!ft_strcmp(command->cmd[0], "export"))
		main->exit_code = ft_export(main, command);
	else if (!ft_strcmp(command->cmd[0], "unset"))
		main->exit_code = ft_unset(main, command);
	else if (!ft_strcmp(command->cmd[0], "cd"))
		main->exit_code = ft_cd(main, command);
	else if (!ft_strcmp(command->cmd[0], "exit"))
		main->exit_code = ft_exit(command);
}

static char	*find_path(char **buf, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (buf[++i])
	{
		tmp = ft_strdup(buf[i]);
		tmp = ft_strjoin(tmp, "/");
		tmp = ft_strjoin(tmp, cmd);
		if (!tmp)
			return (NULL);
		if (!access(tmp, 0))
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

static char	*split_path(t_commands *command, char **envp)
{
	int		i;
	char	**buf;
	char	*ret;

	i = -1;
	while (envp[++i])
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
			break ;
	if (!envp[i])
		return (NULL);
	buf = ft_split(envp[i] + 5, ':');
	ret = find_path(buf, command->cmd[0]);
	i = -1;
	while (buf[++i])
		free(buf[i]);
	free(buf);
	if (!ret)
		return (NULL);
	return (ret);
}

static void	check_command_path(t_main *main, t_commands *command)
{
	char	*path;

	if (ft_strchr(command->cmd[0], '/') != NULL)
	{
		if (execve(command->cmd[0], command->cmd, main->env) < 0)
		{
			printf("minishell: %s: No such file or directory\n",
				   command->cmd[0]);
			exit(127);
		}
	}
	else
	{
		path = split_path(command, main->env);
		if (!path)
		{
			printf("minishell: %s: command not found\n", command->cmd[0]);
			exit(127);
		}
		if (execve(path, command->cmd, main->env) < 0)
		{
			free(path);
			exit(127);
		}
		free(path);
	}
	exit (0);
}

void	check_command(t_main *main, t_commands *command)
{
	if (!main->commands->cmd)
		return ;
	free_dmass(main->env);
	main->env = copy_env_to_mass(main->sort_env);
	if (is_my_command(command))
		exec_my_command(main, command);
	else
	{
		main->pid = fork();
		if (main->pid == 0)
			check_command_path(main, command);
	}
}
