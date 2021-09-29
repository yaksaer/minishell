/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:55:03 by cbilbo            #+#    #+#             */
/*   Updated: 2021/09/28 23:39:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define CLOSE "\001\033[0m\002"
# define BLOD  "\001\033[1m\002"
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"

typedef struct	s_descrip {
	int			def_int;
	int			def_out;
	int 		fd_in;
	int 		fd_out;
}				t_descrip;

typedef struct	s_commands {
	char				**cmd;
	char				**redir;
	int 				input;
	int 				output;
	struct s_commands	*next;
}				t_commands;

typedef struct	s_main {
	char			**env;
	t_dlink_list	*sort_env;
	t_commands		*commands;
}				t_main;

t_dlink_list	*copy_env_to_list(char **env);
char			**copy_env_to_mass(char **env);

/* PARSER */
int			parser(t_main *main);

#endif