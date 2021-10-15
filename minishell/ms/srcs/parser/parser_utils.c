/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:51:49 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/15 19:46:58 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_add_char(char *string, char c)
{
	char	*res;
	int		len;

	len = ft_strlen(string);
	res = (char *)ft_realloc(string, len + 1, len + 2);
	res[len] = c;
	return (res);
}

void	print_commands(t_main *main)
{
	t_commands	*temp;
	int			i;
	int			c;

	temp = main->commands;
	i = 0;
	while (temp != NULL)
	{
		c = -1;
		printf("\n%d pipe\n\ncmds:\n", i);
		while (temp->cmd && temp->cmd[++c] != NULL)
			printf("%s\n", temp->cmd[c]);
		printf("\nredirects:\n");
		c = -1;
		while (temp->redir && temp->redir[++c] != NULL)
			printf("%s\n", temp->redir[c]);
		printf("\ninput = %d, output = %d\n", temp->input, temp->output);
		temp = temp->next;
		i++;
	}
}

void	re_parser(t_main *main, char c)
{
	main->exit_code = 1;
	if (ft_strchr("\'\"", c))
		printf("minishell: %c : Unclosed quotes\n", c);
	else if (ft_strchr("\\;", c))
		printf("minishell: '%c' : Unknown character\n", c);
	commands_clear(&main->commands);
	minishell(main);
}
