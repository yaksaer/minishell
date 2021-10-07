// #include "../../include/minishell.h"

// void 	init_fd(t_descrip *descrip, t_commands *command)
// {
// 	ft_bzero(descrip, sizeof(t_descrip));
// 	descrip->def_in = dup(0);
// 	descrip->def_out = dup(1);
// 	if (command->input)
// 		descrip->fd_in = command->input;
// 	else
// 		descrip->fd_in = dup(descrip->def_in);
// }

// int 	is_my_command(t_main *main, t_commands *command)
// {
// 	if (!ft_strcmp(command->cmd[0], "echo")
// 		|| !ft_strcmp(command->cmd[0], "env")
// 		|| !ft_strcmp(command->cmd[0], "export")
// 		|| !ft_strcmp(command->cmd[0], "unset")
// 		|| !ft_strcmp(command->cmd[0], "pwd")
// 		|| !ft_strcmp(command->cmd[0], "cd")
// 		|| !ft_strcmp(command->cmd[0], "exit"))
// 		return (1);
// 	return (0);
// }

// int		exec_my_command(t_main *main, t_commands *command)
// {
// 	if (!ft_strcmp(command->cmd[0], "echo"))
// 		ft_echo(ft_mass_size(command->cmd), command->cmd);
// 	else if (!ft_strcmp(command->cmd[0], "env"))
// 		ft_env(main->env);
// 	else if (!ft_strcmp(command->cmd[0], "pwd"))
// 		ft_pwd();
// 	else if (!ft_strcmp(command->cmd[0], "export"))
// 		ft_export(main, command);
// 	else if (!ft_strcmp(command->cmd[0], "unset"))
// 		ft_unset(main, command);
// 	else if (!ft_strcmp(command->cmd[0], "cd"))
// 		ft_cd(main, command);
// 	// else if (!ft_strcmp(command->cmd[0], "exit"))
// 	// 	ft_exit(main, command);
// }

// char	*find_path(char **buf, char *cmd)
// {
// 	int		i;
// 	char	*tmp;

// 	i = -1;
// 	while (buf[++i])
// 	{
// 		tmp = ft_strdup(buf[i]);
// 		tmp = ft_strjoin(tmp, "/");
// 		tmp = ft_strjoin(tmp, cmd);
// 		if (!tmp)
// 			return (NULL);
// 		if (!access(tmp, 0))
// 		{
// 			free(cmd);
// 			return (tmp);
// 		}
// 		free(tmp);
// 	}
// 	free(cmd);
// 	return (NULL);
// }

// char	*split_path(t_commands *command, char **envp)
// {
// 	int		i;
// 	char	**buf;
// 	char	*ret;
// 	i = -1;
// 	while (envp[++i])
// 		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
// 			&& envp[i][3] == 'H' && envp[i][4] == '=')
// 			break ;
// 	if (!envp[i])
// 		return (NULL);
// 	buf = ft_split(envp[i] + 5, ':');
// 	ret = find_path(buf, command->cmd[0]);
// 	i = -1;
// 	while (buf[++i])
// 		free(buf[i]);
// 	free(buf);
// 	if (!ret)
// 		return (NULL);
// 	return (ret);
// }

// int		check_command_path(t_main *main, t_commands *command)
// {
// 	char	*path;

// 	if (ft_strchr(command->cmd[0], '/') != NULL)
// 	{
// 		if (execve(command->cmd[0], command->cmd, main->env) < 0)
// 		{
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		path = split_path(command, main->env);
// 		if (!path)
// 			return (1);
// 		if (execve(path, command->cmd, main->env) < 0)
// 		{
// 			free(path);
// 			exit(1);
// 		}
// 		free(path);
// 	}
// 	return (0);
// }

// void	set_out(t_descrip *desc, t_commands *command)
// {
// 	int		fd_pipe[2];

// 	if (!command->next)
// 	{
// 		if (command->output)
// 			desc->fd_out = command->output;
// 		else
// 			desc->fd_out = dup(desc->def_out);
// 	}
// 	else
// 	{
// 		pipe(fd_pipe);
// 		desc->fd_out = fd_pipe[1];
// 		desc->fd_in = fd_pipe[0];
// 	}
// 	if (command->output)
// 		dup2(command->output, 1);
// 	else
// 		dup2(desc->fd_out, 1);
// 	close(desc->fd_out);
// }

// void	set_in(t_descrip *desc, t_commands *command)
// {
// 	if (command->input)
// 		dup2(command->input, 0);
// 	else
// 		dup2(desc->fd_in, 0);
// 	close(desc->fd_in);
// }

// void	reset_fd(t_descrip *descrip)
// {
// 	dup2(descrip->def_in, 0);
// 	dup2(descrip->def_out, 1);
// 	close(descrip->def_out);
// 	close(descrip->def_in);
// }

// void 	check_command(t_main *main, t_commands *command)
// {
// 	int 	t;

// 	if (!main->commands->cmd)
// 		return ;
// 	if (is_my_command(main, main->commands))
// 		exec_my_command(main, main->commands);
// 	else
// 	{
// 		main->pid = fork();
// 		if (main->pid == 0)
// 		{
// 			check_command_path(main, command);
// 			exit(0);
// 		}
// 		waitpid(main->pid, &t, 0);
// 	}
// }

// int 	get_command(t_main *main)
// {
// 	t_descrip	descrip;
// 	t_commands	*tmp;

// 	main->desc = &descrip;
// 	init_fd(main->desc, main->commands);
// 	tmp = main->commands;
// 	while (tmp)
// 	{
// 		set_in(&descrip, tmp);
// 		set_out(&descrip, tmp);
// 		check_command(main, tmp);
// 		tmp = tmp->next;
// 	}
// 	reset_fd(&descrip);
// 	return (0);
// }
