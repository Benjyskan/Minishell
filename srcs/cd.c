#include "minishell.h"

/*
** set_env_pwds set PWD each time I cd
*/

static void	set_env_pwd(char **env)
{
	char	path[PATH_MAX];
	char	*new;
	int		i;

	getcwd(path, PATH_MAX);
	i = get_linenumber_from_env("PWD", env);
	if (!(new = ft_strnew(4 + ft_strlen(path))))
		ERROR_MEM;
	ft_strcpy(new, "PWD=");
	ft_strcpy(&new[4], path);
	free(env[i]);
	env[i] = new;
}

void	cd_dash(char **args, t_myenv *my_env)
{
	char	tmp[PATH_MAX];

	getcwd(tmp, PATH_MAX);
	if (ft_strcmp(args[1], "-") == 0)
	{
		if (!access(my_env->old_pwd, F_OK))
			chdir(my_env->old_pwd);
		else
			cd_not_found_str(my_env->old_pwd);
	}
	else
		cd_invalid_option(args, my_env);
	ft_strcpy(my_env->old_pwd, tmp);
	set_env_pwd(my_env->envp);
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
			cd_not_found_str(args[1]);
			//cd_not_found(args, my_env->envp);
		return (1);
	}
	ft_strcpy(my_env->old_pwd, tmp);
	set_env_pwd(my_env->envp);
	return (0);
}

void	cd_tilde(char **args, t_myenv *my_env)
{
	char	home_save[PATH_MAX];
	int		home_size;
	int		i;
	char	tmp[PATH_MAX];

	getcwd(tmp, PATH_MAX);
	if (!get_line_from_env("HOME", my_env->envp)
			|| *get_line_from_env("HOME", my_env->envp) == 0)
	{
		ft_putendl_fd("No $home variable set.", 2);
		return ;
	}
	i = 1;
	ft_bzero(home_save, PATH_MAX);
	ft_strcpy(home_save, get_line_from_env("HOME", my_env->envp));
	home_size = ft_strlen(home_save);
	if (chdir(home_save) == -1)
		cd_not_found_str(home_save);
	ft_strcpy(my_env->old_pwd, tmp);
	set_env_pwd(my_env->envp);
	return ;
}

/*
** cd -: cd to OLD_PWD (and print the absolute path ? no)
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
	//if (!args[1] || args[1][0] == '~')
	if (!args[1])
		cd_tilde(args, my_env);
	if (args[1] && args[1][0] == '-')//bof
		cd_dash(args, my_env);//i can put this line in the statement above
	else if (args[1] && cd_arg(args, my_env))//bof
		return (1);
	return (0);
}
