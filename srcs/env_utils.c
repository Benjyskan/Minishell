#include "minishell.h"

/*
** return 1 if env_line is = search until '='
** return 0 otherwise
*/

int		get_envvar_name(char *search, char *env_line)
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
** (use get_envvar_name)
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
		if ((equal_pos = get_envvar_name(search, env[i])))
			return (env[i] + equal_pos + 1);
	}
	return (NULL);
}

char	**get_all_env_path(char *path)
{
	char	**tab;

	if (!path)
		return (NULL);
	tab = ft_strsplit(path, ':');
	return (tab);
}

void	add_env_var(char **my_env, char *new_var)
{
	(void)my_env;
	(void)new_var;
	//add a new var at the end of env and null terminat env
}

/*
** if envp: MALLOC
** else: return NULL  or should i malloc a mini_env ?
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
		my_env = NULL;// ou mini_env ?
		return (my_env);
	}
	tab_len = get_ntab_len(envp);
	printf("env len: %d\n", tab_len);
	if (!(my_env = (char**)malloc(sizeof(char**) * (tab_len + 1))))
		ERROR_MEM;
	my_env[tab_len] = NULL;
	i = -1;
	while (++i < (int)tab_len)
		my_env[i] = ft_strdup(envp[i]);
	return (my_env);
}

/*
** set my_env via address
** init_env should return 0 if it fail
*/

int		init_env(char **envp, t_myenv *my_env)
{
	if (*envp)
	{
		my_env->envp = cpy_envp(envp);
		//degueu, si on suppr HOME
		ft_bzero(my_env->home, PATH_MAX);
		ft_strcpy(my_env->home,
				get_line_from_env("HOME", my_env->envp));
	}
	else
	{
		ft_putendl("env is NULL");
		ft_bzero(my_env->home, PATH_MAX);
		ft_strcpy(my_env->home, getcwd(my_env->home, PATH_MAX));
	}
	ft_putendl(my_env->home);
	//set PWD
	//my_env.pwd = //getpwd();
	return (1);
}
