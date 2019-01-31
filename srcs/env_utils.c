#include "minishell.h"

char	*get_env_path(char **envp)
{
	int		i;

	if (!envp)
	{
		printf("ENV IS NULL\n");
		return (NULL);
	}
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp("PATH=", envp[i], 5)))
			return (envp[i]);
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

	if (!*envp)
	{
		ft_putendl("env is NULL");
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
*/

int		init_env(char **envp, t_myenv *my_env)
{
	if (*envp)
	{
		my_env->envp = cpy_envp(envp);
	}
	//set HOME
	ft_bzero(my_env->home, PATH_MAX);
	ft_strcpy(my_env->home, HOME);
	//set PWD
	//my_env.pwd = //getpwd();
	return (1);
}

/*char	*append_path(const char *path, const char *prog_name)//malloc
{
	int		len;
	char	*res;
	int		pathlen;
	int		dirlen;

	if (!path)
		return (ft_strdup((char*)prog_name));
	pathlen = ft_strlen(path);
	dirlen = ft_strlen(prog_name);
	len = pathlen + dirlen + 1;
	if (!(res = ft_strnew(len + 1)))
		ERROR_MEM;
	ft_strncpy(res, path, pathlen);
	res[pathlen] = '/';
	ft_strncpy((res + pathlen + 1), prog_name, dirlen);
	return (res);
}*/
