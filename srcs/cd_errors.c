/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:18:12 by penzo             #+#    #+#             */
/*   Updated: 2019/03/09 11:18:25 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_not_found_str(char *str)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	cd_permi_denied(char **args, char **env)
{
	(void)env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": Permission denied", 2);
}

void	cd_invalid_option(char **args, t_myenv *my_env)
{
	(void)my_env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(" invalid option", 2);
	ft_putendl_fd("cd: usage: cd [dir]", 2);
}
