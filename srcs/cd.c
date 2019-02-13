#include "minishell.h"

void	cd_dash(char **args, t_myenv *my_env)
{
	char	tmp[PATH_MAX];

	getcwd(tmp, PATH_MAX);
	if (ft_strcmp(args[1], "-") == 0)
	{
		if (!access(my_env->old_pwd, F_OK))
		{
			chdir(my_env->old_pwd);
			ft_putendl(my_env->old_pwd);
		}
		else
			cd_not_found_str(my_env->old_pwd);
	}
	else
		cd_invalid_option(args, my_env);
	ft_strcpy(my_env->old_pwd, tmp);
}

int		cd_arg(char **args, t_myenv *my_env)
{
	char	tmp[PATH_MAX];

	getcwd(tmp, PATH_MAX);
	if (chdir(args[1]) == -1)
	{
		if (!access(args[1], F_OK))
			cd_permi_denied(args, my_env->envp);
		else
			cd_not_found(args, my_env->envp);
		return (1);
	}
	ft_strcpy(my_env->old_pwd, tmp);
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
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		//TODO: Expand ~
		if (chdir(get_line_from_env("HOME", my_env->envp)) == -1)
			cd_not_found_str(get_line_from_env("HOME", my_env->envp));
		//return (0);
	}
	else if (args[1] && args[1][0] == '-')//bof
		cd_dash(args, my_env);//i can put this line in the statement above
	else if (args[1] && cd_arg(args, my_env))//bof
		return (1);
	return (0);
}
