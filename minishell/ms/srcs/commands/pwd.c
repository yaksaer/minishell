/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:47 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:48 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_main *main)
{
	char	path[1024];
	t_node	*tmp;

	ft_bzero(path, FILENAME_MAX);
	if (getcwd(path, FILENAME_MAX) == NULL)
	{
		tmp = find_key_node(main->sort_env, "PWD");
		if (tmp)
			printf("%s\n", tmp->data + 4);
		else
			printf("%s\n", main->vault_pwd + 4);
	}
	else
		printf("%s\n", path);
	return (0);
}
