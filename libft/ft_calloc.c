/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:22:47 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 14:51:02 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;

	mem = (unsigned char *)malloc(nmemb * size);
	if (!mem)
		return (NULL);
	mem = ft_bzero(mem, nmemb * size);
	return (mem);
}
