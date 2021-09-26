#include "libft.h"

void    ft_putstr(char *str)
{
    size_t	i;

    i = 0;
    if (!str)
        return ;
    while (str[i])
    {
        write(1, &str[i], sizeof(char));
        i++;
    }
}
