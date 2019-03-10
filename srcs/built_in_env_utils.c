/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:23:11 by penzo             #+#    #+#             */
/*   Updated: 2019/03/10 15:28:49 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** do_envvar_exist() return 1 if the envvar exist
** return 0 if not
*/

int		do_envvar_exist(char *what, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (strcmp_before_equal(what, envp[i]))
			return (1);
	}
	return (0);
}

void	print_env(char **args, char **env)
{
	int		i;

	(void)args;
	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
}

char	**dup_env(char **env)
{
	int		tab_len;
	char	**new_env;
	int		i;

	tab_len = get_ntab_len(env);
	if (!(new_env = (char**)malloc(sizeof(char**) * (tab_len + 1))))
		ERROR_MEM;
	new_env[tab_len] = 0;
	i = -1;
	while(++i < tab_len)
	{
		if (!(new_env[i] = ft_strdup(env[i])))
			ERROR_MEM;
	}
	return (new_env);
}

/*
** is_no_cmd_left start on args[1]
** return 1 if it remain cmds in args
*/

int		is_no_cmd_left(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (args[i][0] != '-' && !ft_strchr(args[i], '='))
				return (0);
	}
	return (1);
}
/*
** is_last_cmd return 1 if no cmd are left
** return 0 otherwise
*/

int		is_last_cmd(char **args)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (args[i][0] != '-' && !ft_strchr(args[i], '='))
			return (0);
	}
	return (1);
}

int		is_valid_options(char *arg)
{
	int		i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] != 'i')
		{
			print_env_usage(arg[i]);
			return (0);
		}
	}
	return (1);
}
