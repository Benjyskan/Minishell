#include "minishell.h"

/*
** should i imitate exit status ?
*/

void	my_env_function(char **args, char **env)
{
	int		i;

	ft_putendl("---------MY ENV function-----------");
	(void)args;
	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
}

int		my_setenv(const char *name, const char *value, int overwrite)
{
	return (0);
}

int		my_unsetenv(const char *name)
{
	return (0);
}
