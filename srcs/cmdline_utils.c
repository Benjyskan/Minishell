/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:19:00 by penzo             #+#    #+#             */
/*   Updated: 2019/03/12 13:44:02 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/*
** split the command line, expand variables,
** send it to get_right_prog()
** and return to the loop
**
** the "if (!*args)" is for blank lines
*/

void	transform_cmdline(char *line, t_myenv *my_env)
{
	char	**args;

	if (!(args = strsplit_multi(line, " \t")))
		ERROR_MEM;
	if (!*args)
	{
		ft_memdel((void*)&args);
		return ;
	}
	if (!(expand_vars(args, my_env->envp)))
	{
		free_nultab(args);
		return ;
	}
	get_right_prog(args, my_env);
}

/*
** fill the buffer bytes per bytes
** reallocif necessary
*/

void	fill_buf(char **buf, int *i, char c, int *buf_len)
{
	char	*tmp;

	if (*i == (*buf_len))
	{
		if (!(tmp = ft_strnew(*buf_len * 2)))
			ERROR_MEM;
		*buf_len *= 2;
		ft_strcpy(tmp, *buf);
		ft_memdel((void*)&(*buf));
		*buf = tmp;
	}
	(*buf)[(*i)++] = c;
}
