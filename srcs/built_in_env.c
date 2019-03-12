/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:22:36 by penzo             #+#    #+#             */
/*   Updated: 2019/03/12 19:10:50 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** return an args of size size
*/

static char	**get_short_cmd(char **args, int size, t_myenv *tmp_env)
{
	char	**short_cmd;
	int		i;

	(void)tmp_env;
	if (!(short_cmd = (char**)malloc(sizeof(char**) * (size + 1))))
		ERROR_MEM;
	i = -1;
	while (++i < size)
	{
		if (!(short_cmd[i] = ft_strdup(args[i])))
			ERROR_MEM;
	}
	short_cmd[i] = 0;
	return (short_cmd);
}

static char	**get_cur_envcmd(char **args, t_myenv *tmp_env)
{
	int		i;
	char	**short_cmd;

	i = 0;
	while (args[++i])
	{
		if (args[i][0] != '-' && !ft_strchr(args[i], '='))
			break ;
	}
	if (!(short_cmd = get_short_cmd(args, i, tmp_env)))
		ERROR_MEM;
	return (short_cmd);
}

/*
** search format: *=*
** return the index from env
*/

static int	get_envline_number(char *search, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strcmp_until_c(search, env[i], '='))
			return (i);
	}
	return (-1);
}

int			exec_env(char **short_cmd, t_myenv *tmp_env, int mod)
{
	int		i;
	int		index;

	i = 0;
	while (short_cmd[++i])
	{
		if (short_cmd[i][0] == '-' && !mod)
		{
			if (is_valid_options(short_cmd[i]))
				tmp_env->envp = env_i_options(tmp_env->envp);
			else
				return (0);
		}
		else if (ft_strchr(short_cmd[i], '='))
		{
			if ((index = get_envline_number(short_cmd[i], tmp_env->envp))
					!= -1)
				tmp_env->envp = replace_env_var(short_cmd[i], index
						, tmp_env->envp);
			else
				tmp_env->envp = add_env_var(short_cmd[i], tmp_env->envp);
		}
	}
	return (1);
}

void		my_env_function(char **args, t_myenv *my_env)
{
	t_myenv tmp_env;
	char	**cur_envcmd;
	int		i;

	if (!(tmp_env.envp = dup_env(my_env->envp)))
		ERROR_MEM;
	if (!(tmp_env.old_pwd = ft_strnew(0)))//test
		ERROR_MEM;
	i = 0;
	while (!is_last_cmd(args + i))
	{
		cur_envcmd = get_cur_envcmd(args + i, &tmp_env);
		i += get_ntab_len(cur_envcmd);
		if (!exec_env(cur_envcmd, &tmp_env, 0))
			return (free_double_nultab(tmp_env.envp, cur_envcmd));
		free_nultab(cur_envcmd);
	}
	cur_envcmd = dup_env(args + i);
	if (ft_strcmp(cur_envcmd[0], "env") == 0)
		my_env_norm(cur_envcmd, &tmp_env);
	else
	{
		exec_env(cur_envcmd, &tmp_env, 1);
		get_right_prog(cur_envcmd, &tmp_env);
	}
	free_nultab(tmp_env.envp);
	//
	free(tmp_env.old_pwd);//test
	//
}
