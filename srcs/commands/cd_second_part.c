/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:41 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:42 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hyphen_proc(t_main *main, char *old_dir)
{
	t_node	*tmp;
	char	*dir;
	int		ret;

	ret = 0;
	tmp = find_key_node(main->unsort_env, "OLDPWD");
	if (!tmp)
		ret = printf("Minishell: cd: OLDPWD not set\n");
	dir = ft_strdup(tmp->data + 7);
	if (!dir)
		error_n_exit(NULL, NULL, 1);
	if (dir[0] != '\0')
		ret = specified_dir(dir);
	printf("%s\n", dir);
	change_env(main, old_dir, dir);
	free(dir);
	if (ret > 0)
		return (1);
	return (0);
}
