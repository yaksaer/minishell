#include "minishell.h"

char	*split_after_equal_sing(char *src)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	i++; // чтобы пропустить знак =
	len = ft_strlen(src) - i;
	if (!len)
		return (NULL);
	res = ft_calloc(1, len + 1);
	// TODO проверка на ошибку маллока
	j = 0;
	while (src[i])
		res[j++] = src[i++];
	return (res);
}

char	*split_before_equal_sing(const char *src)
{
	size_t	i;
	size_t	len;
	char	*res;

	len = 0;
	while (src[len] && src[len] != '=')
		len++;
	res = ft_calloc(1, len + 1);
	// TODO проверка на ошибку маллока
	i = 0;
	while (i < len)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}

char	*get_env_value(char *dest, t_list *env)
{
	char	*env_name;
	char	*env_value;

	env_value = NULL;
	while (env && env->content)
	{
		env_name = split_before_equal_sing(env->content);
		if (env_name && (ft_strcmp(dest, env_name) == 0))
		{
			env_value = split_after_equal_sing(env->content);
			free(env_name);
			break ;
		}
		free(env_name);
		env = env->next;
	}
	return (env_value);
}

void	set_env_value(char *dest, t_list *env, char *value)
{
	char	*env_name;

	while (env && env->next)
	{
		env_name = split_before_equal_sing(env->content);
		// TODO = проверка env_name на NULL и выход с ошибкой маллока
		if (strcmp(dest, env_name) == 0)
		{
			free(env->content);
			env->content = ft_strjoin(dest, value);
			free(env_name);
			return ;
		}
		free(env_name);
		env = env->next;
	}
}

void	shlvl_counter(t_list *env)
{
	int		level;
	char	*value;

	value = get_env_value("SHLVL", env);
	level = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(level);
	if (level < 0)
		set_env_value("SHLVL", env, "0");
	else if (level == 1000)
		set_env_value("SHLVL", env, "");
	else if (level > 1000)
	{
		ft_putstr("21sh: warning: shell level (");
		ft_putstr(value);
		ft_putendl(") too high, resetting to 1");
		set_env_value("SHLVL", env, "1");
	}
	else
		set_env_value("SHLVL", env, value);
}

void	reset_fds(t_mainstruct *main)
{
	main->fdin = -1;
	main->fdout = -1;
	main->pipein = -1;
	main->pipeout = -1;
	main->pid = -1;
}

t_list 	*copy_env_to_list(char **env)
{
	t_list	*res_list;
	int		i;

	res_list = NULL;
	i = 0;
	while (env[i])
	{
		ft_lstadd_back(&res_list, ft_lstnew(ft_strdup(env[i])));
		// TODO: нужно подумать про защиту маллока в каждой из этих функций:
		// TODO: нужна ли защита, и что делать при ошибке маллока
		i++;
	}
	return (res_list);
}

void init_mainsturct(t_mainstruct *main, char **env)
{
	ft_bzero(main, sizeof(t_mainstruct));
	main->in = dup(STDIN_FILENO);
	main->out = dup(STDOUT_FILENO);
	main->env_list = copy_env_to_list(env);
	main->secret_env_list = copy_env_to_list(env);
	reset_fds(main);
}

void	signal_code_analyzer(t_mainstruct *main)
{
	ft_putendl(" here");
	if (g_signal_code == SIGINT && main->pid)
	{
		ft_putstr("\b\b  \n21sh$ ");
		main->exit_code = SH_INTERRUPT_BY_SIGNAL;
		main->exit = true;
	}
	else if (g_signal_code == SIGINT && !main->pid)
	{
		ft_putstr("\n");
		main->exit_code = CMD_INTERRUPT_BY_SIGNAL;
	}
	else if (g_signal_code == SIGQUIT && !main->pid)
	{
		ft_putendl("Quit: 3");
		main->exit_code = CMD_QUIT_BY_SIGNAL;
	}
	else if (g_signal_code == SIGQUIT && main->pid)
		ft_putstr("\b\b  \b\b");
}

void get_signal_code(int code)
{
	g_signal_code = code;
}

int main(int argc, char **argv, char **env)
{
	t_mainstruct main;

	init_mainsturct(&main, env);
	shlvl_counter(main.env_list);
	while (!main.exit)
	{
		g_signal_code = 0;
		signal(SIGINT, &get_signal_code); // ctrl + c
		signal(SIGQUIT, &get_signal_code); // 'ctrl + \'
		if (g_signal_code)
			signal_code_analyzer(&main);
		if (main.exit)
			break ;
		parse(&main);
		exec_commands(&main);
		free_commands(&main.cmds);
	}
	return (main.exit_code);
}
