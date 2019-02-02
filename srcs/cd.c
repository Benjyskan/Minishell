#include "minishell.h"

void	cd_not_found(char **args, char **env)
{
	(void)env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	cd_invalid_option(char **args, t_myenv *my_env)
{
	(void)my_env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(" invalid option", 2);
	ft_putendl_fd("cd: usage: cd [dir]", 2);
}

void	cd_dash(char **args, t_myenv *my_env)
{
	if (ft_strcmp(args[1], "-") == 0)
	{
		//what if no OLDPWD ?
		chdir(get_line_from_env("OLDPWD", my_env->envp));
		ft_putendl(get_line_from_env("OLDPWD", my_env->envp));
	}
	else
		cd_invalid_option(args, my_env);
}

int		cd_arg(char **args, t_myenv *my_env)
{
	if (chdir(args[1]) == -1)
	{
		//expand '-'
		//so i should change cd_not_found args
		cd_not_found(args, my_env->envp);
		return (1);
	}
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
	//else if (args[1] && ft_strncmp(args[1], "-", 1) == 0)//bof
	else if (args[1] && args[1][0] == '-')//bof
		cd_dash(args, my_env);//i can put this line in the statement above
	else if (args[1] && cd_arg(args, my_env))//bof
		return (1);
	return (0);
}
