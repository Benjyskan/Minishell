/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:19:22 by penzo             #+#    #+#             */
/*   Updated: 2019/03/12 13:49:57 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check_setenv_args return 0 if invalid
*/

static int	check_setenv_args(char **args)
{
	int		i;
	int		arg_cnt;

	arg_cnt = count_args(args);
	if (arg_cnt >= 4)
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

static void	reset_env_var(char **args, char **env)
{
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

static char	*strjoin_equal(char *s1, char *s2)
{
	int		len;
	char	*res;
	int		i;

	if (s2)
		len = ft_strlen(s1) + ft_strlen(s2) + 1;
	else
		len = ft_strlen(s1) + 1;
	if (!(res = ft_strnew(len)))
		ERROR_MEM;
	ft_strcpy(res, s1);
	i = 0;
	while (res[i])
		i++;
	res[i++] = '=';
	if (s2)
		ft_strcpy(&res[i], s2);
	return (res);
}

/*
** syntax: setenv TOTO TATA
*/

void		my_setenv(char **args, t_myenv *my_env)
{
	char	*env_var;

	if (!args[1])
	{
		my_env_function(args, my_env);
		return ;
	}
	if (!check_setenv_args(args))
		return ;
	if ((env_var = get_line_from_env(args[1], my_env->envp)))
		reset_env_var(args, my_env->envp);
	else
	{
		env_var = strjoin_equal(args[1], args[2]);
		my_env->envp = add_env_var(env_var, my_env->envp);
		ft_memdel((void*)&env_var);
	}
}
