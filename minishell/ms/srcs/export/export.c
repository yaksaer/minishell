#include "../minishell.h"

char 	**sort_str(char **argv, int zero, int argc)
{
	int		i;
	int		j;
	char	*x;
	char	*temp;

	i = zero;
	j = argc - 1;
	x = argv[(zero + argc) / 2];
	while(i <= j)
	{
		while((ft_strcmp(argv[i], x) < 0) && (i < argc))
			i++;
		while((ft_strcmp(argv[j], x) > 0) && (j > zero))
			j--;
		if (i <= j)
		{
			temp = (char *)ft_calloc(ft_strlen(argv[i]), sizeof(char));
			if (!temp)
				return (NULL);
			ft_strcpy(temp, argv[i]);
			ft_strcpy(argv[i], argv[j]);
			ft_strcpy(argv[j], temp);
			i++;
			j--;
			free(temp);
		}
	}
	if(zero < j)
		sort_str(argv, zero, j);
	if(i < argc)
		sort_str(argv, i, argc);
	return (argv);
}

char 	**copy_argv(char **argv)
{
	char 	**ret;
	int 	i;
	int 	j;
	int 	size;

	size = 0;
	while (argv[size])
		size++;
	ret = (char**)calloc(size, sizeof(char*));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (++i < size)
		ret[j++] = ft_strdup(argv[i]);
	ret[j] = '\0';
	return (ret);
}

char 	**copy_env(char **env, int count)
{
	char 	**ret;
	int 	i;
	int 	size;

	size = 0;
	while (env[size])
		size++;
	ret = (char**)calloc(count + size + 1, sizeof(char*));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < size)
		ret[i] = ft_strdup(env[i]);
	ret[i] = '\0';
	return (ret);
}

char 	**add_to_env(int argc, char **argv, char **env)
{
	int 	size;
	int 	i;
	char 	**res;

	res = copy_env(env, argc - 1);
	size = 0;
	while (res[size])
		size++;
	i = 0;
	while (i < argc)
	{
		if (ft_isdigit(argv[i][0]))
			return (NULL);
		res[size] = ft_strdup(argv[i]);
		if (!res[size])
			return (NULL);
		size++;
		i++;
	}
	res[size] = '\0';
	return (res);
}

int		main(int argc, char **argv, char **env)
{
	int 			i;
	static char 	**res;
	char 			**tmp_argv;

	i = 1;
	if (argc > 1)
	{
		tmp_argv = copy_argv(argv);
		if (argc > 2)
			tmp_argv = sort_str(tmp_argv, 0, argc - 1);
		printf("declare -x %s\n", tmp_argv[0]);
		res = add_to_env(argc - 1, tmp_argv, env);
	}
	else
	{
		res = copy_env(env, argc - 1);
		while (res[i])
			printf("declare -x %s\n", res[i++]);
	}
//	i = 0;
//	while (res[i])
//		printf("declare -x %s\n", res[i++]);
	return (0);
}

