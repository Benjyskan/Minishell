#include "minishell.h"

static void	env_no_args(char **args, char **env)
{
	int		i;

	(void)args;
	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
}

void		my_env_function(char **args, char **env)
{
	env_no_args(args, env);
}
