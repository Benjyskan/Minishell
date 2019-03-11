/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:03:43 by penzo             #+#    #+#             */
/*   Updated: 2019/03/11 19:28:06 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_str_digit(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
	}
	return (1);
}

void			strjoin_equal_nomalloc(char *s1, char *s2, char *result)
{
	int		i;
	int		j;

	ft_bzero(result, PATH_MAX);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	result[i] = '=';
	j = -1;
	if (!s2)
		return ;
	while (s2[++j])
		result[++i] = s2[j];
}

void			append_path_nomalloc(char *env_path,
				char *prog_name, char *result)
{
	int		i;
	int		j;

	ft_bzero(result, PATH_MAX);
	i = -1;
	while (env_path[++i])
		result[i] = env_path[i];
	result[i] = '/';
	j = -1;
	while (prog_name[++j])
		result[++i] = prog_name[j];
}

/*
** return ('=' offset) if search is equal to env_line name
** return 0 otherwise
*/

int				strcmp_before_equal(char *search, char *env_line)
{
	int		i;

	i = -1;
	while (env_line[++i] != '=')
	{
		if (search[i] != env_line[i])
			return (0);
	}
	if (!search[i])
		return (i);
	return (0);
}
