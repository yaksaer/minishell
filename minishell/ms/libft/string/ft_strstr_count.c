#include "../libft.h"

int	ft_strstr_count(char *dest, char *needle)
{
	int 	i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (dest[i])
	{
		j = 0;
		while (needle[j] == dest[i + j])
		{
			if (!(needle[j + 1]))
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (count);
}