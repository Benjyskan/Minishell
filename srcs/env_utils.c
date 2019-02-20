#include "minishell.h"

/*
** return ('=' offset) if search is equal to env_line name
** return 0 otherwise
*/

int		strcmp_before_equal(char *search, char *env_line)
{
	int		i;

	//printf("search: {%s} in: {%s}\n", search, env_line);
	i = -1;
	while (env_line[++i] != '=' )//&& env_line[i] && search[i])
	{
		if (search[i] != env_line[i])
			return (0);
	}
	return (i);
}

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
	tab = ft_strsplit(path, ':');
	return (tab);
}

/*
** realloc envp with +1 line
*/

//add a new var at the end of env and null terminat env
//void	add_env_var(char *new_var, char **envp)
char	**add_env_var(char *new_var, char **envp)
{
	int		line_count;
	char	**new;

	ft_putendl("ICICICICICI");
	line_count = 0;
	/////
	//while (envp[line_count])
	//	line_count++;
	//// OU
	line_count = get_ntab_len(envp);
	if (!(new = (char**)malloc(sizeof(char**) * (line_count + 2))))
		ERROR_MEM;
	line_count = -1;
	while (envp[++line_count])
		new[line_count] = ft_strdup(envp[line_count]);
	//envp[line_count] = ft_strdup(new_var);
	new[line_count] = ft_strdup(new_var);
	new[line_count + 1] = 0;
	ft_putendl("---");
	ft_put_nultab(new);
	ft_putendl("---");
	//free plz
	free_nultab(envp);
	//envp = new;
	return (new);//a chier
}

char 	**create_minienv(void)
{
	int		init_lines = 2;//!!!
	char	**envp;

	if (!(envp = (char**)malloc(sizeof(char**) * init_lines)))
		ERROR_MEM;
	if (!(envp[0] = ft_strnew(6 + 8)))
		ERROR_MEM;
	ft_strcpy(envp[0], "SHLVL=1");
	envp[init_lines - 1] = NULL;
	return (envp);
}

/*
** if envp: MALLOC
** else: return NULL  or should i malloc a mini_env ? yes, which malloc too
*/

//envp is NULL terminated
//when adding a new variable, replace the last line (NULL) and add a new NULL
char	**cpy_envp(char **envp)
{
	int	tab_len;
	char			**my_env;
	int				i;

	if (!*envp)//useless, vu que je check dans la fonct precedente
	{
		ft_putendl("WEHEHEY, tu ne me veras jamais !!!!");
		my_env = NULL;// ou mini_env ?
		return (my_env);
	}
	tab_len = get_ntab_len(envp);
	if (!(my_env = (char**)malloc(sizeof(char**) * (tab_len + 1))))
		ERROR_MEM;
	my_env[tab_len] = NULL;
	i = -1;
	while (++i < (int)tab_len)
		my_env[i] = ft_strdup(envp[i]);
	set_shlvl(&my_env);
	ft_putendl("+++");
	ft_put_nultab(my_env);
	ft_putendl("+++");
	return (my_env);
}

/*
** set my_env via address
** init_env should return 0 if it fail
*/

int		init_env(char **envp, t_myenv *my_env)
{
	ft_bzero(my_env->old_pwd, PATH_MAX);//well placed ??
	if (*envp)
	{
		my_env->envp = cpy_envp(envp);
		//degueu, si on suppr HOME
		ft_bzero(my_env->home, PATH_MAX);//useless ?
		//ft_strcpy(my_env->home,
		//		get_line_from_env("HOME", my_env->envp));//usefull ? apparement non
	}
	else
	{
		ft_putendl("env is NULL");//tejme 
		ft_bzero(my_env->home, PATH_MAX);
		//malloc some shit
		my_env->envp = create_minienv();
	}
	return (1);
}
