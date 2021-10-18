#include "../../include/minishell.h"

void	print_export(t_dlink_list *env)
{
	t_node	*tmp;
	int		i;
	int		flag;

	tmp = env->head;
	while (tmp)
	{
		i = 0;
		flag = 0;
		ft_putstr_fd("declare -x ", 1);
		while (tmp->data[i])
		{
			if (tmp->data[i] == '=')
			{
				ft_putchar_fd(tmp->data[i++], 1);
				ft_putchar_fd('"', 1);
				flag = 1;
			}
			if (tmp->data[i])
				ft_putchar_fd(tmp->data[i++], 1);
		}
		if (flag == 1)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

int	replace_value(char **src, char *var)
{
	int		i;
	char	*ret;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	tmp1 = str_get_key(var);
	while (src[++i])
	{
		tmp2 = str_get_key(src[i]);
		if (ft_strcmp(tmp2, tmp1) == 0)
		{
			free(src[i]);
			ret = ft_calloc(ft_strlen(var) + 1, sizeof(char));
			if (!ret)
				return (1);
			ret = ft_strcpy(ret, var);
			src[i] = ret;
			free(tmp2);
			break ;
		}
		free(tmp2);
	}
	free(tmp1);
	return (0);
}
