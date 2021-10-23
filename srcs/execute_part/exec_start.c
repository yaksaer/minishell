/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:54 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/20 20:14:50 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_fd(t_descrip *descrip, t_commands *command)
{
	ft_bzero((void *) descrip, sizeof(t_descrip));
	descrip->def_in = dup(0);
	descrip->def_out = dup(1);
	if (command->input)
		descrip->fd_in = command->input;
	else
		descrip->fd_in = dup(descrip->def_in);
}

static void	set_out(t_descrip *desc, t_commands *command)
{
	int		fd_pipe[2];

	if (!command->next)
	{
		if (command->output)
			desc->fd_out = command->output;
		else
			desc->fd_out = dup(desc->def_out);
	}
	else
	{
		pipe(fd_pipe);
		desc->fd_out = fd_pipe[1];
		desc->fd_in = fd_pipe[0];
	}
	if (command->output)
		dup2(command->output, 1);
	else
		dup2(desc->fd_out, 1);
	close(desc->fd_out);
}

static void	set_in(t_descrip *desc, t_commands *command)
{
	if (command->input)
		dup2(command->input, 0);
	else
		dup2(desc->fd_in, 0);
	close(desc->fd_in);
}

static void	reset_fd(t_descrip *descrip)
{
	dup2(descrip->def_in, 0);
	dup2(descrip->def_out, 1);
	close(descrip->def_out);
	close(descrip->def_in);
}

int	get_command(t_main *main)
{
	t_descrip			descrip;
	t_commands			*tmp;

	init_fd(&descrip, main->commands);
	main->pid = 0;
	tmp = main->commands;
	while (tmp)
	{
		if (main->pid)
		{
			waitpid(main->pid, 0, 0);
			kill(main->pid, SIGKILL);
		}
		switsch_signals(main, tmp);
		set_in(&descrip, tmp);
		set_out(&descrip, tmp);
		check_command(main, tmp);
		tmp = tmp->next;
	}
	reset_fd(&descrip);
	wait_child(main);
	return (0);
}
