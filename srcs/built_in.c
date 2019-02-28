/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:20:05 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 19:20:06 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	my_exit(char **args, t_myenv *my_env)
{
	int		ac;

	ac = 0;
	while (args[ac])
		ac++;
	if (ac == 1)
	{
		ft_putendl_fd("exit caca", 2);
		free_nultab(args);
		free_nultab(my_env->envp);
		printf("address: %p\n", my_env->old_pwd);
		ft_memdel((void*)&my_env->old_pwd);
		exit(0);
	}
	else if (ac > 1 && !is_str_digit(args[1]))
	{
		ft_putendl_fd("exit", 2);
		exit_not_digit(args, my_env);
	}
	else if (ac == 2)
		exit_numeric(args, my_env);
	else
		exit_many_args();
}

/*
** return 1 if prog_name is a built_in
** return 0 otherwise
** maybe useless ?
*/

int			check_built_in(char **args, t_myenv *my_env)
{
	if ((ft_strcmp(args[0], "exit")) == 0)
		my_exit(args, my_env);
	else if ((ft_strcmp(args[0], "echo")) == 0)
		my_echo(args, my_env);
	else if ((ft_strcmp(args[0], "cd")) == 0)
		my_cd(args, my_env);
	else if ((ft_strcmp(args[0], "env")) == 0)
		my_env_function(args, my_env->envp);
	else if ((ft_strcmp(args[0], "setenv")) == 0)
		my_setenv(args, &my_env->envp);
	else if ((ft_strcmp(args[0], "unsetenv")) == 0)
		my_unsetenv(args, &my_env->envp);
	else
		return (0);
	return (1);
}
