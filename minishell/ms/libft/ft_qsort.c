/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:04:59 by cbilbo            #+#    #+#             */
/*   Updated: 2021/06/28 20:17:28 by cbilbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // 426135 326145 321645 123645

static int	srt(int *arr, int first, int last)
{
	int	i;
	int	j;
	int	m;

	i = first;
	j = last;
	m = arr[(i + j) / 2];
	while (1)
	{
		while (arr[i] < m)
			i++;
		while (arr[j] > m)
			j--;
		if (i >= j)
			return (j);
		ft_swap(&arr[i++], &arr[j--]);
	}
}

void	ft_qsort(int *arr, int first, int last)
{
	long int	middle;

	if (first < last)
	{
		middle = srt(arr, first, last);
		ft_qsort(arr, first, middle);
		ft_qsort(arr, middle + 1, last);
	}
}
