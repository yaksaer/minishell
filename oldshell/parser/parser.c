#include "../minishell.h"

void	skip_spaces(const char *str, size_t *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
		   || (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		*i += 1;
}

int is_space_quote_or_operator(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v' || c == '|' || c == ';' || c == '<' || c == '>'
		|| c == '\'' || c == '"')
		return (1);
	return (0);
}

t_command	*get_next_command(const char *line, size_t *i)
{
	size_t		k; // запоминаем позицию *i
	size_t 		j; // для копирования строки
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	// TODO malloc error
	k = *i;

	while (line[*i] && !(is_space_quote_or_operator(line[*i]))
		&& !((line[*i] == '&' && line[*i + 1] == '&')))
		*i += 1;
	if (*i != k)
	{
		cmd->str = ft_calloc(1, sizeof(char) * (*i - k + 1));
		// TODO malloc error
		j = 0;
		while (k < *i)
			cmd->str[j++] = line[k++];
		cmd->type = CMD;
	}
	else if (ft_isspace(line[*i]))
		*i += 1;
	else if (line[*i] == '|')
	{
		*i += 1;
		cmd->type = PIPE;
		if (line[*i] && line[*i] == '|') {
			*i += 1;
			cmd->type = OR;
		}
	}
	else if (line[*i] == ';')
	{
		*i += 1;
		cmd->type = SEMICOLON;
	}
	else if (line[*i] == '<')
	{
		*i += 1;
		cmd->type = REDIRIN;
	}
	else if (line[*i] == '>')
	{
		*i += 1;
		cmd->type = REDIROUT;
		if (line[*i] && line[*i] == '>') {
			*i += 1;
			cmd->type = AREDIROUT;
		}
	}
	else if (line[*i] == '&' && line[*i + 1] == '&')
	{
		*i += 2;
		cmd->type = AND;
	}
	return (cmd);
}

void	push_back(t_command **cmds, t_command *cmd)
{
	t_command	*last;
	t_command	*tmp;

	last = *cmds;
	if (!*cmds)
		*cmds = cmd;
	else
	{
		while (last)
		{
			if (last->next == NULL)
				break;
			tmp = last;
			last = last->next;
			last->prev = tmp;
		}
		last->next = cmd;
		cmd->prev = last;
	}
}

void	get_commands(t_mainstruct *main)
{
	size_t 		i;
	t_command	*cmd;

	i = 0;
	while (i < ft_strlen(main->line))
	{
		skip_spaces(main->line, &i);
		cmd = get_next_command(main->line, &i);
		push_back(&main->cmds, cmd);
	}
}

void check_quotes(t_mainstruct *main)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (main->line[i])
	{
		if (i > 0 && main->line[i - 1] == '\\')
			;
		else if (flag == 0 && main->line[i] == '\'')
			flag = 1;
		else if (flag == 0 && main->line[i] == '\"')
			flag = 2;
		else if (flag == 1 && main->line[i] == '\'')
			flag = 0;
		else if (flag == 2 && main->line[i] == '\"')
			flag = 0;
		i++;
	}
	if (flag)
	{
		ft_putendl_fd("21sh: error - wrong number of quotes", STDERR_FILENO);
		free_n_null_ptr((void **)&main->line);
		main->exit_code = SYNTAX_ERROR;
	}
}

void	parse(t_mainstruct *main)
{

	ft_putstr("21sh$ ");
	get_next_line(STDIN_FILENO, &main->line);
	// TODO если gnl вернула -1?
//	history(main);
	check_quotes(main);
	get_commands(main);
	free_n_null_ptr((void **)&main->line);
}

