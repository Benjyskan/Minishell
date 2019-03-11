/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:01:00 by penzo             #+#    #+#             */
/*   Updated: 2019/03/11 15:59:34 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	too_many_args(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": Too many arguments.", 2);
}

void	too_few_args(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": Too few arguments.", 2);
}

void	print_env_usage(char c)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: env [-i] [name=value ...] [utility [argument ...]]"
			, 2);
}

void	no_such_file(char **args, char *arg, char **env)//??
{
	(void)env;
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	file_name_too_long(char *file_name)
{
	ft_putstr_fd(file_name, 2);
	ft_putendl_fd(": File name too long", 2);
}
