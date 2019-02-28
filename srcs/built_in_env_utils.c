#include "minishell.h"

/*
** do_envvar_exist() return 1 if the envvar exist
** return 0 if not
*/

int		do_envvar_exist(char *what, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (strcmp_before_equal(what, envp[i]))
			return (1);
	}
	return (0);
}
