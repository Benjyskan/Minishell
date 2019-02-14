#include "minishell.h"

/*int		strcmp_before_equal(char *what, char *equal_line)
{
	int		i;

	i = -1;
	while (what[++i] && equal_line[i] && equal_line[i] != '=')
	{
		if (what[i] != equal_line[i])
			return (0);
	}
	if (equal_line[i + 1] == '=')
		return (1);
	return (0);
}*/

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
