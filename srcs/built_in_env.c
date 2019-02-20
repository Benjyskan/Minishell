#include "minishell.h"

/*
** check_equal return 0 if '=' is found
** return -1 otherwise
*/

/*static int	check_equal(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (0);
	}
	return (-1);
}*/

static void	env_no_args(char **args, char **env)
{
	int		i;

	ft_putendl("---------MY ENV function-----------");
	(void)args;
	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
}

void		my_env_function(char **args, char **env)
{
	if (!args[1])
		env_no_args(args, env);
}

/*int		my_setenv(const char *name, const char *value, int overwrite)
{
	return (0);
}

int		my_unsetenv(const char *name)
{
	return (0);
}*/
