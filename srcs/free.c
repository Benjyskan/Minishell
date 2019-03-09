#include "minishell.h"

void	free_nultab(char **tab)
{
	int		i;

	if (!tab /*|| !*tab*/)//????
		return ;
	i = -1;
	while (tab[++i])
		ft_memdel((void*)&tab[i]);
	ft_memdel((void*)&tab);
}
