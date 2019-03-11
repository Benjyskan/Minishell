/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:22:36 by penzo             #+#    #+#             */
/*   Updated: 2019/03/11 15:26:45 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** return a malloced empty env
*/

static char	**env_i_options(char **env)
{
	//ft_putendl("is -i");
	free_nultab(env);
	if (!(env = malloc(sizeof(char**) * 1)))
		ERROR_MEM;
	env[0] = NULL;
	return (env);
}

/*static int	first_env_check(char **args, char **env)
{
	int		i;

	(void)env;
	i = -1;
	while (args[++i])
	{
		if (i > 0 && args[i][0] != '-' && !ft_strchr(args[i], '='))//pas sure
			return (1);
		if (args[i][0] == '-' && !is_valid_options(args[i]))
			return (0);
	}
	return (1);
}*/

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

//move to libft
int		ft_strcmp_until_c(char *s1, char *s2, char c)
{
	int		i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (-1);
	i = -1;
	while (s1[++i] != c)
	{
		if (s1[i] != s2[i])
			return (1);
	}
	if (s2[i] == c)
		return (0);
	return (1);
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

static int	exec_env(char **short_cmd, t_myenv *tmp_env, int mod)
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
			{
				free_nultab(short_cmd);
				free_nultab(tmp_env->envp);//test11 is good
				return (0);
			}
		}
		else if (ft_strchr(short_cmd[i], '='))
		{
			if ((index = get_envline_number(short_cmd[i], tmp_env->envp)) != -1)
				tmp_env->envp = replace_env_var(short_cmd[i], index, tmp_env->envp);
			else
				tmp_env->envp = add_env_var(short_cmd[i], tmp_env->envp);
		}
	}
	//free_nultab(short_cmd);//nul ? oui
	return (1);
}

void		my_env_function(char **args, t_myenv *my_env)
{
	t_myenv tmp_env;
	char	**cur_envcmd;
	int		i;
	//save full args ? useless, car (arg + i)

	if (!(tmp_env.envp = dup_env(my_env->envp)))
		ERROR_MEM;
	i = 0;
	while (!is_last_cmd(args + i))
	{
		cur_envcmd = get_cur_envcmd(args + i, &tmp_env);
		i += get_ntab_len(cur_envcmd);
		//exec_env(cur_envcmd, &tmp_env, 0);
		if (!exec_env(cur_envcmd, &tmp_env, 0))
			return ;
		free_nultab(cur_envcmd);//test
	}
	//cur_envcmd = get_cur_envcmd(args + i, &tmp_env);//1
	//cur_envcmd = args + i;//2
	cur_envcmd = dup_env(args + i);
	if (ft_strcmp(cur_envcmd[0], "env") == 0)
	{
		exec_env(cur_envcmd, &tmp_env, 0);
		print_env(NULL, tmp_env.envp);
		free_nultab(cur_envcmd);//test
	}
	else
	{
		exec_env(cur_envcmd, &tmp_env, 1);
		get_right_prog(cur_envcmd, &tmp_env);
	}
	free_nultab(tmp_env.envp);
}
