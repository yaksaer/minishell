#include <stdio.h>
#include "libft/libft.h"

int main ()
{
    char    *str;
    char    *ret;
    int     n;

    str = ft_strdup("lets do it now");
    n = ft_strlen(str);
    ret = ft_realloc(str, 2);
    ret[n] = '1';
    ret[n + 1] = '2';
    ret[n + 2] = '3';
    ret[n + 3] = '4';
    ret[n + 4] = '5';
    ret[n + 5] = '6';
    ret[n + 6] = '7';
    printf("%zu\n", ft_strlen(ret));
//    printf("%s\n", ret);
	return 0;
}