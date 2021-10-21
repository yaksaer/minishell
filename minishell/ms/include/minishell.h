/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:55:03 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/20 19:52:16 by cbilbo           ###   ########.fr       */
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
# define BEGIN "\001\033[49;32m\002"

typedef struct s_descrip
{
	int					def_in;
	int					def_out;
	int					fd_in;
	int					fd_out;
}				t_descrip;

typedef struct s_commands
{
	char				**cmd;
	char				**redir;
	int					input;
	int					output;
	struct s_commands	*next;
}				t_commands;

typedef struct s_main
{
	char				*vault_pwd;
	int					flag_exit;
	int					exit_code;
	int					flag;
	char				**env;
	t_dlink_list		*sort_env;
	t_dlink_list		*unsort_env;
	t_commands			*commands;
	struct sigaction	sigac;
	int					pid;
}				t_main;

extern t_main	*g_main;

int				rl_replace_line(char *line, int undo);
/*UTILS*/
void			ft_dlist_insert_head(t_dlink_list *list, size_t index, \
									char *data);
int				proc_shlvl(t_main *main);
char			*path_error(int flag, char *cmd);
t_dlink_list	*copy_env_to_list(char **env);
char			**copy_env_to_mass(t_dlink_list *env);
char			*get_env_key(t_node *node);
char			*str_get_key(char *var);
int				ft_mass_size(char **str);
int				add_quotes(t_dlink_list *env_list);
char			*add_quotes_util(char *str);
int				ft_mass_size(char **str);
int				check_key(char *val, char *prog);
int				sort_dlist(t_dlink_list *dlist);
t_main			*init_main(char **envp);
void			minishell(t_main *main);
void			free_dmass(char **str);
void			error_n_exit(void *buf, void**buf2, int flag);
/*EXECUTE*/
int				get_command(t_main *main);
void			check_command(t_main *main, t_commands *command);
int				is_my_command(t_commands *command);
void			wait_child(t_main *main);
/*COMMANDS*/
int				ft_echo(int argc, char **argv);
int				ft_env(t_main *main);
int				ft_pwd(t_main *main);
int				ft_export(t_main *main, t_commands *command);
int				unsort_list_proc(char *comnd, t_dlink_list *env);
int				add_to_unsort_list(t_dlink_list *env, char *cmd, char *key);
void			print_export(t_dlink_list *env);
int				replace_value(char **src, char *var);
int				add_to_list(t_dlink_list *env, char *var, char *key);
int				ft_unset(t_main *main, t_commands *command);
void			list_unset(t_dlink_list *env, char *val);
int				ft_cd(t_main *main, t_commands *command);
void			add_pwd_env(t_main *main, char *str);
t_node			*find_key_node(t_dlink_list *env, char *key);
int				ft_exit(t_main *main, t_commands *commands);
/* PARSER */
int				parser(t_main *main);
void			start_pars(t_main *main, char *string);
/* Parse words from readline string
Return 0 if no pipe or 1 if string has continue */
int				parse_command(t_main *main, t_commands *command, char **string, \
																	char *res);
/* Parse one command word */
char			*parse_word(t_main *main, char **string);
/* Checker of parser's results */
void			print_commands(t_main *main);

/*REDIRECT*/

/*Parse word with redirect*/
void			parse_redirect(t_commands *cmd, char **string);
/* open path with needed parameters
r is type of angle brackers
n is number of angle brackers
Return value is file descriptor*/
int				open_redir(char *path, char r, int n);
/* Parse path and change input/output
r = type of angle brackers*/
void			redir_path(t_main *main, t_commands *com, char *path, char r);
/*Choose type of redirection*/
void			handle_redir(t_main *main);

/*HEREDOC*/

/*Parse specification of heredoc
't' is tabs
'q' is quotations
Return keyword*/
char			*parse_heredoc(char *str, int *qt);
/*Parse heredoc string 
Return clearly output*/
char			*put_heredoc(t_main *main, char *dest, char *src, int qt);
/*Heredoc childproc
key = keyword
qt = parameters of tabs and quotes
Return file descriptor of heredoc*/
void			heredoc_process(t_main *main, char *key, int qt);
/*Main heredoc function*/
void			ft_heredoc(t_main *main, int *input, char *string);

/*SPECIAL CHARACTERS*/

/*Replace environment variable*/
char			*put_env(t_main *main, char **string);
/*Modificate words with quotes*/
char			*parse_quotation(t_main *main, char **string, char quote);

/* UTILS FOR STRUCT T_COMMAND */

/*Create new command struct*/
t_commands		*commands_new(char **cmd, char **redir, int input, int output);
/*Put command struct at the end of list*/
void			commands_back(t_commands **command, t_commands *new);
/*Delete one command struct from lists*/
void			commands_delone(t_commands *command);
/*Clear command lists*/
void			commands_clear(t_commands **command);
/*Increase cmd or redirect from command struct
number = position of string
Return actual massive string*/
char			**add_string_to_massive(char ***dest, char **src, int number);

/* SIGNAL_HANDLERS*/
/* Signals from Minishell*/
void			handle_signals(int sig, siginfo_t *info, void *ucontext);
/* Signals from heredoc*/
void			her_signals(int sig, siginfo_t *info, void *ucontext);
/* Signals for cmd*/
void			cmd_signals(int sig);
/* Create and switch signals
*s = string of parameters:
'c' = create sigac;
'm' = main sigac;
'h' = heredoc sigac;
'0' = turn off sigac;
'1' = turn on sigac;*/
void			redirect_signals(struct sigaction *sigac, char *s);
void			switsch_signals(t_main *main, t_commands *cmd);

/* UTILS */
/* add char to string with realloc*/
char			*ft_add_char(char *string, char c);
void			re_parser(t_main *main, char c);
void			check_pipe(t_main *main, t_commands *com);
#endif