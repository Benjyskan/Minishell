/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:19:12 by penzo             #+#    #+#             */
/*   Updated: 2019/03/12 18:49:05 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** set_env_pwds set PWD each time I cd
*/

static void	set_env_pwd(char ***env)
{
	char	*cwd;
	char	*new;
	int		i;

	if (!(cwd = getcwd(NULL, 0)))
		ERROR_MEM;
	i = get_linenumber_from_env("PWD", *env);
	if (!(new = ft_strnew(4 + ft_strlen(cwd))))
		ERROR_MEM;
	ft_strcpy(new, "PWD=");
	ft_strcpy(&new[4], cwd);
	if (i == -1)
		*env = add_env_var(new, *env);
	else
	{
		ft_memdel((void*)&(*env)[i]);
		(*env)[i] = new;
	}
	ft_memdel((void*)&cwd);
}

void		cd_dash(char **args, t_myenv *my_env)
{
	char	*cwd;

	cwd = NULL;
	if (!(cwd = getcwd(NULL, 0)))
		ERROR_MEM;
	if (!my_env->old_pwd)
	{
		cd_not_found_str(my_env->old_pwd);
		ft_memdel((void*)&cwd);
		return ;
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		if (!access(my_env->old_pwd, F_OK))
			chdir(my_env->old_pwd);
		else
			cd_not_found_str(my_env->old_pwd);
	}
	else
		cd_invalid_option(args, my_env);
	if (my_env->old_pwd)//test
		ft_memdel((void*)&my_env->old_pwd);
	my_env->old_pwd = ft_strdup(cwd);
	set_env_pwd(&my_env->envp);
	ft_memdel((void*)&cwd);
}

int			cd_arg(char **args, t_myenv *my_env)
{
	char	*cwd;

	if (!(cwd = getcwd(NULL, 0)))
		ERROR_MEM;
	if (chdir(args[1]) == -1)
	{
		if (!access(args[1], F_OK))
			cd_permi_denied(args, my_env->envp);
		else
			cd_not_found_str(args[1]);
		ft_memdel((void*)&cwd);
		return (1);
	}
	ft_memdel((void*)&my_env->old_pwd);
	my_env->old_pwd = ft_strdup(cwd);
	set_env_pwd(&my_env->envp);
	ft_memdel((void*)&cwd);
	return (0);
}

void		cd_tilde(char **args, t_myenv *my_env)
{
	char	*cwd;

	(void)args;
	if (!(cwd = getcwd(NULL, 0)))
		ERROR_MEM;
	if (!get_line_from_env("HOME", my_env->envp)
			|| *get_line_from_env("HOME", my_env->envp) == 0)
	{
		ft_putendl_fd("No $home variable set.", 2);
		ft_memdel((void*)&cwd);
		return ;
	}
	if (chdir(get_line_from_env("HOME", my_env->envp)) == -1)
		cd_not_found_str(get_line_from_env("HOME", my_env->envp));
	ft_memdel((void*)&my_env->old_pwd);
	my_env->old_pwd = ft_strdup(cwd);
	set_env_pwd(&my_env->envp);
	ft_memdel((void*)&cwd);
	return ;
}

int			my_cd(char **args, t_myenv *my_env)
{
	if (!args[1])
		cd_tilde(args, my_env);
	if (args[1] && args[1][0] == '-')
		cd_dash(args, my_env);
	else if (args[1] && cd_arg(args, my_env))
		return (1);
	return (0);
}
