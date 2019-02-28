/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:21:58 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 19:22:03 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	output_echo_line(char **args, t_myenv *my_env)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (i != 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
	}
	ft_putchar_fd('\n', 1);
}

void		my_echo(char **args, t_myenv *my_env)
{
	output_echo_line(args, my_env);
}
