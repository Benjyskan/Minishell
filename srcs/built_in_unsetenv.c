#include "minishell.h"


static int		count_valid_args(char **args, char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (args[++i])
	{
		if (get_line_from_env(args[i], env))
			count++;
	}
	return (count);
}

/*
** return 1 if env_line isn't found within args
*/

int		cmp_envvarname_with_args(char *env_line, char **args)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (strcmp_before_equal(args[i], env_line))
			return (0);
	}
	return (1);
}

char	**cpy_unsetenv(char **args, char **env, char **new_env)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
	{
		if (cmp_envvarname_with_args(env[i], args))
		{
			if (!(new_env[j++] = ft_strdup(env[i])))
				ERROR_MEM;
		}
	}
	free_nultab(env);
	new_env[j] = 0;
	return (new_env);
}

void	my_unsetenv(char **args, char ***env)
{
	int		arg_cnt;
	int		tab_len;
	char	**new_env;

	if (!args[1])
	{
		too_few_args(args[0]);
		return ;
	}
	if (!(arg_cnt = count_valid_args(args, *env)))
		return ;
	tab_len = get_ntab_len(*env);
	if (!(new_env = malloc(sizeof(char**) * (tab_len - arg_cnt + 1))))//hmm
		ERROR_MEM;
	*env = cpy_unsetenv(args, *env, new_env);
}
