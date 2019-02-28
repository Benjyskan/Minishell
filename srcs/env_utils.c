#include "minishell.h"

/*
** return a pointer to the correct line, after the '='
** (use strcmp_before_equal)
** return NULL otherwise
*/

char	*get_line_from_env(char *search, char **env)
{
	int		i;
	int		equal_pos;

	if (!search || !env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if ((equal_pos = strcmp_before_equal(search, env[i])))
			return (env[i] + equal_pos + 1);
	}
	return (NULL);
}

/*
** return the line number of the 'search' in env
** return -1 on errors
*/

int		get_linenumber_from_env(char *search, char **env)
{
	int		i;

	if (!search || !env)
		return (-1);
	i = -1;
	while (env[++i])
	{
		if (strcmp_before_equal(search, env[i]))
			return (i);
	}
	return (-1);
}

char	**get_all_env_path(char *path)
{
	char	**tab;

	if (!path)
		return (NULL);
	if (!(tab = ft_strsplit(path, ':')))
		ERROR_MEM;
	return (tab);
}

/*
** realloc envp with +1 line
** and add the string new_var to envp
*/

char	**add_env_var(char *new_var, char **envp)
{
	int		line_count;
	char	**new;

	//line_count = 0;//useless ?
	line_count = get_ntab_len(envp);
	if (!(new = (char**)malloc(sizeof(char**) * (line_count + 2))))
		ERROR_MEM;
	line_count = -1;
	while (envp[++line_count])
	{
		if (!(new[line_count] = ft_strdup(envp[line_count])))
			ERROR_MEM;
	}
	if (!(new[line_count] = ft_strdup(new_var)))
		ERROR_MEM;
	new[line_count + 1] = 0;
	free_nultab(envp);
	return (new);
}
