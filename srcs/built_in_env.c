/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:22:36 by penzo             #+#    #+#             */
/*   Updated: 2019/03/09 23:09:51 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(char **args, char **env)
{
	int		i;

	(void)args;
	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
}

static char	**env_i_options(char **env)
{
	//ft_putendl("is -i");
	free_nultab(env);
	if (!(env = malloc(sizeof(char**) * 1)))
		ERROR_MEM;
	env[0] = NULL;
	return (env);
}

static int	is_valid_options(char *arg)
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

//should check -i; if check -u: ignore next args
static void	check_env_options(char **args, char **env)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		
	}
}

static char	**dup_env(char **env)
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

static int	is_no_cmd_left(char **args)
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

/*static void	env_args(char **args, char **env)
{
	int		i;
	char	**tmp_env;

	tmp_env = dup_env(env);
	i = -1;//ici ??
	while (args[++i])
	{
		if (!ft_strncmp(args[i], "-i", 2))
		{
			tmp_env = env_i_options(tmp_env);
		}
		else if (ft_strchr(args[i], '='))
		{
			if (get_linenumber_from_env(args[i], tmp_env) == -1)
				tmp_env = add_env_var(args[i], tmp_env);
		}
		else if (!ft_strcmp(args[i], "env"))
		{
			my_env_function(args + i + 0, tmp_env);
			return ;
		}
		else if (args[i])//exec
		{
			env_exec(args + i, tmp_env);
			return ;//useless ?
		}
	}
	//check_env_options(args, tmp_env);
	free_nultab(tmp_env);

}*/

static void	env_args(char **args, t_myenv *my_env)
{
	int		i;
	//char	**tmp_env;
	t_myenv tmp_my_env;

	ft_putendl("1111");
	tmp_my_env.envp = dup_env(my_env->envp);
	ft_putendl("2222");
	i = -1;//ici ??
	while (args[++i])
	{
		if (!ft_strncmp(args[i], "-i", 2))
			tmp_my_env.envp = env_i_options(tmp_my_env.envp);
		else if (ft_strchr(args[i], '='))
		{
			if (get_linenumber_from_env(args[i], tmp_my_env.envp) == -1)
				tmp_my_env.envp = add_env_var(args[i], tmp_my_env.envp);
		}
		//else
		//else if (!is_no_cmd_left(args) && !ft_strcmp(args[i], "env"))//NULLL
		else if (is_no_cmd_left(args))
		{
			printf("i=%d\n", i);
			env_exec(args + i, &tmp_my_env.envp);
			//my_env_function(args + i, tmp_my_env.envp);
			return ;
		}
		else if (i > 0)
		{
			ft_putendl("HHHHHHKKKKKKKKK");
			ft_put_nultab(tmp_my_env.envp);
		}
	}
	//check_env_options(args, tmp_my_env.envp);
	//free_nultab(&tmp_my_env.envp);//check
}

static int	first_env_check(char **args, char **env)
{
	int		i;
	i = -1;
	while (args[++i])
	{
		if (i > 0 && args[i][0] != '-' && !ft_strchr(args[i], '='))//pas sure
			return (1);
		if (args[i][0] == '-' && !is_valid_options(args[i]))
			return (0);
	}
	return (1);
}

void		my_env_function(char **args, t_myenv *my_env)
{
	if (!args[1])//|| is_no_cmd_left(args)
	{
		ft_putendl("################No args[1]");
			print_env(args, my_env->envp);
	}
	else if (!is_no_cmd_left(args))
	{
		ft_putendl("################!is_no_cmd_left(args)");
		if (!first_env_check(args, my_env->envp))
			return ;
		env_args(args + 1, my_env);
	}
	else
	{
		ft_putendl("*&^*&^*&^*&^*&^*&^*&^*&^");
		env_args(args + 1, my_env);
	}
}

/*void		my_env_function(char **args, char **env)
{
	if (!args[1])
		print_env(args, env);
	else
	{
		if (!first_env_check(args, env))
			return ;
		env_args(args, env);
		//print_env(args, env);
	}
}*/
