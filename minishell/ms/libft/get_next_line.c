/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:38:22 by cbilbo            #+#    #+#             */
/*   Updated: 2021/04/15 20:54:35 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	result(int vr, char **rem, char **line)
{
	char	*res;
	char	*temp;
	int		i;

	i = 0;
	while (*rem && (*rem)[i] != '\0' && (*rem)[i] != '\n')
		i++;
	if (*rem && (*rem)[i] == '\n')
	{
		res = (char *)ft_calloc((i + 1), sizeof(char));
		if (!res)
			return (-1);
		ft_memcpy(res, *rem, i);
		temp = ft_strdup(&(*rem)[i + 1]);
		ft_allocfree((void *)&*rem);
		*rem = temp;
	}
	else
	{
		res = ft_strdup(ft_ter_s(*rem == NULL, "\0", *rem));
		ft_allocfree((void *)&(*rem));
	}
	if (res)
		*line = res;
	return (ft_ter_i(vr == 0 && !*rem, 0, 1));
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			vr;
	static char	*rem[255];
	char		*temp;

	vr = read(fd, buf, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || vr == -1)
		return (-1);
	*line = NULL;
	while (vr > 0)
	{
		buf[vr] = '\0';
		if (!rem[fd])
			rem[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(rem[fd], buf);
			ft_allocfree((void *)&(rem[fd]));
			rem[fd] = temp;
		}
		if (ft_strchr(rem[fd], '\n'))
			break ;
		vr = read(fd, buf, BUFFER_SIZE);
	}
	return (result(vr, &rem[fd], &*line));
}
