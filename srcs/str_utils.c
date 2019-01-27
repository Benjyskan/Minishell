#include "minishell.h"

int		is_str_digit(char *str)
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
