#include "minishell.h"

void	cd_not_found(char **args, char **env)
{
	(void)env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	cd_dash(char **args, t_myenv *my_env)
{
	chdir(get_line_from_env("OLDPWD", my_env->envp));
	ft_putendl(get_line_from_env("OLDPWD", my_env->envp));
}

int		cd_arg(char **args, t_myenv *my_env)
{
	if (chdir(args[1]) == -1)
	{
		cd_not_found(args, my_env->envp);
		return (1);
	}
	//else
	//	printf("%s\n", args[1]);
	return (0);
}

/*
** cd -: cd to OLD_PWD (and print the absolute path ?)
** cd : cd to ~
** cd return 0 if succesfull
** cd return 1 if it fail
**
** cd reset PWD and OLDPWD even if they don't exist anymore
*/

//i need to refresh PWD and OLDPWD:
//should i use my struct, or create a mini_env ?
int		my_cd(char **args, t_myenv *my_env)
{
	ft_putendl("MY CD");
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		//TODO: Expand ~
		if (chdir(my_env->home) == -1)
		{
			cd_not_found(args, my_env->envp);
			printf("~\n");//env HOME=sldkfjsldkfj ./minishell
		}
		return (0);
	}
	else if (args[1] && ft_strcmp(args[1], "-") == 0)
		cd_dash(args, my_env);
	else if (args[1] && cd_arg(args, my_env))//bof
		return (1);
	return (0);
}
