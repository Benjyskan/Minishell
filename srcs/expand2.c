/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:24:07 by penzo             #+#    #+#             */
/*   Updated: 2019/03/11 20:50:56 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *needle)
{
	int		i;
	char	*var_name;

	i = 1;
	while (ft_isalnum(needle[i]))
		i++;
	if (i == 1 || ft_isdigit(needle[1]))
	{
		ft_putendl_fd("Syntax Error", 2);
		return (NULL);
	}
	if (!(var_name = ft_strnew(i)))
		ERROR_MEM;
	ft_strncpy(var_name, &needle[1], i - 1);
	return (var_name);
}

int		check_dollars_undefined(char *arg, char *tmp)
{
	undefined_variable(tmp);
	ft_memdel((void*)&tmp);
	ft_memdel((void*)&arg);
	return (0);
}

void	set_i_j(int *i, int i_val, int *j, int j_val)
{
	*i = i_val;
	*j = j_val;
}
