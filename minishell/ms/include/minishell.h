/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:55:03 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/04 15:33:29 by marvin           ###   ########.fr       */
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
	int				pid;
}				t_main;
/*UTILS*/
t_dlink_list	*copy_env_to_list(char **env);
char			**copy_env_to_mass(char **env);
char			*get_env_key(t_node *node);
char			*str_get_key(char *var);
int				ft_mass_size(char **str);
int				add_quotes(t_dlink_list *env_list);
char			*add_quotes_util(char *str);
int				ft_mass_size(char **str);
int				check_key(char *val, char *prog);
int				sort_dlist(t_dlink_list *dlist);
int 			init_main(t_main *main, char **envp);
/*EXECUTE*/
int				get_command(t_main *main);
/*COMMANDS*/
int				ft_echo(int argc, char **argv);
int				ft_env(char **env);
int				ft_pwd(void);
int				ft_export(t_main *main, t_commands *command);
int				ft_unset(t_main *main, t_commands *command);
/* PARSER */
int				parser(t_main *main);
void			start_pars(t_main *main, char *string);

/* UTILS FOR STRUCT T_COMMAND */
t_commands		*commands_new(char **cmd, char **redir, int input, int output);
void			commands_back(t_commands **command, t_commands *new);
void			commands_delone(t_commands *command);
void			commands_clear(t_commands **command);
char			**add_string_to_massive(char ***dest, char **src, int number);
#endif