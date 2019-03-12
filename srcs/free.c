/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:18:18 by penzo             #+#    #+#             */
/*   Updated: 2019/03/12 18:18:48 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nultab(char **tab)
{
	int		i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_memdel((void*)&tab[i]);
	ft_memdel((void*)&tab);
}

void	free_double_nultab(char **tab1, char **tab2)
{
	free_nultab(tab1);
	free_nultab(tab2);
}

int		free_nultab_ret_int(char **tab, int ret)
{
	free_nultab(tab);
	return (ret);
}
