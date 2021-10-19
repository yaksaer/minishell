/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:54 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:52:07 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_dmass(char **str)
{
	int		i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}

void	wait_child(t_main *main)
{
	int		stat;

	if (main->pid != 0)
	{
		waitpid(main->pid, &stat, 0);
		if (WIFEXITED(stat) && WEXITSTATUS(stat))
			main->exit_code = WEXITSTATUS(stat);
	}
}

void	add_new_shlvl(t_main *main, int n)
{
	char	*buf;

	buf = ft_strjoinm("SHLVL=", ft_itoa(n), 2);
	if (!buf)
		error_n_exit(NULL, NULL, 1);
	add_to_list(main->sort_env, buf, "SHLVL");
	buf = ft_strdup(buf);
	if (!buf)
		error_n_exit(NULL, NULL, 1);
	add_to_unsort_list(main->unsort_env, buf, "SHLVL");
}

int	proc_shlvl(t_main *main)
{
	t_node	*tmp;
	char	*key;

	tmp = main->sort_env->head;
	while (tmp)
	{
		key = get_env_key(tmp);
		if (!key)
			error_n_exit(NULL, NULL, 1);
		if (ft_strcmp(key, "SHLVL") == 0)
		{
			free(key);
			break ;
		}
		tmp = tmp->next;
		free(key);
	}
	if (tmp)
		add_new_shlvl(main, ft_atoi(tmp->data + 6) + 1);
	return (0);
}
