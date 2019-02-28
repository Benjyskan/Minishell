/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:23:11 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 19:23:56 by penzo            ###   ########.fr       */
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
