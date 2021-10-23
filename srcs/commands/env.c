/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:48:34 by cbilbo            #+#    #+#             */
/*   Updated: 2021/10/19 16:48:35 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_main *main)
{
	t_node	*tmp;

	tmp = main->unsort_env->head;
	while (tmp)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}
