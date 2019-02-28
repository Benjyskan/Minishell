/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:22:36 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 19:22:36 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_no_args(char **args, char **env)
{
	int		i;

	(void)args;
	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
}

void		my_env_function(char **args, char **env)
{
	env_no_args(args, env);
}
