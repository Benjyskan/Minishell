/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:02:02 by penzo             #+#    #+#             */
/*   Updated: 2019/03/12 17:02:03 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": command not found.", 2);
}

void	undefined_variable(char *var_name)
{
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd(": Undefined variable.", 2);
}

void	exec_permission_denied(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": Permission denied.", 2);
}

void	var_must_begin_letter(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": Variable name must begin with a letter.", 2);
}

void	var_is_not_alphanum(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": Variable name must contain alphanumeric characters.", 2);
}
