#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>

# define CMD 1
# define PIPE 2
# define SEMICOLON 3
# define REDIRIN 4
# define REDIROUT 5
# define AREDIROUT 6
# define AND 7
# define OR 8

// exit codes

# define SH_INTERRUPT_BY_SIGNAL 1
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127
# define CMD_INTERRUPT_BY_SIGNAL 130
# define CMD_QUIT_BY_SIGNAL 131
# define EXIT_NOT_NUMERIC 255
# define SYNTAX_ERROR 258

int		g_signal_code;

typedef struct	s_command
{
	int					type;
	char 				*str;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct	s_history
{
	int 			fd;
	int 			count;
	int 			arr_count;
	t_Node			*curent_Node;
	t_DblLinkedList *hist_list;
}	t_history;

typedef struct	s_mainstruct
{
	t_history 		*hist;
	t_command 		*cmds;
	t_list			*env_list;
	t_list			*secret_env_list;
	char 			*line;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipein;
	int				pipeout;
	int				exit_code;
	bool			exit;
	int 			ret;
	pid_t			pid;
	int				no_exec;
}	t_mainstruct;

int 	history(t_mainstruct *main);
void	parse(t_mainstruct *main);
void	exec_commands(t_mainstruct *main);
void	exit_from_minishell(t_mainstruct *main);
void	free_commands(t_command **cmds);
char	*get_env_value(char *dest, t_list *env);

#endif
