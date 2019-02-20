#include "minishell.h"

/* 
** check_setenv_args return 0 if invalid
*/

int		check_setenv_args(char **args)
{
	int		i;

	if (args[3])
	{
		too_many_args(args[0]);
		return (0);
	}
	if (ft_isdigit(args[1][0]))
	{
		var_must_begin_letter(args[0]);
		return (0);
	}
	i = -1;
	while (args[1][++i])
	{
		if (!ft_isalnum(args[1][i]) && args[1][i] != '_')
		{
			var_is_not_alphanum(args[0]);
			return (0);
		}
	}
	return (1);
}

void	reset_env_var(char **args, char **env)
{
	//char	tmp[ARG_MAX];
	int		i;
	int		j;
	int		new_size;

	i = get_linenumber_from_env(args[1], env);
	new_size = ft_strlen(args[1]) + 1;
	ft_memdel((void*)&env[i]);
	if (args[2])
		new_size += ft_strlen(args[2]);
	if (!(env[i] = ft_strnew(new_size)))
		ERROR_MEM;
	ft_strcpy(env[i], args[1]);
	j = 0;
	while (env[i][j])
		j++;
	env[i][j++] = '=';
	if (args[2])
		ft_strcpy(env[i] + j, args[2]);
}

/*
** syntax: setenv TOTO TATA
*/

//TODO: check [a-zA-Z0-9_], for env too (T.T)
//and doesn't start with number
//TODO: if no args, exec env
//***env ?
void	my_setenv(char **args, char ***env)
{
	char	*env_var;
	char	test[ARG_MAX];//really really DEGUEU
	//int		i;

	if (!args[1])
	{
		my_env_function(args, *env);
		return ;
	}
	if (!check_setenv_args(args))
		return ;
	if ((env_var = get_line_from_env(args[1], *env)))
		reset_env_var(args, *env);
	else
	{
		//test = NULL;//is it cleaner ?
		if (args[2])
			strjoin_equal_nomalloc(args[1], args[2], test);
		else
			strjoin_equal_nomalloc(args[1], NULL, test);
		*env = add_env_var(test, *env);
	}
}
