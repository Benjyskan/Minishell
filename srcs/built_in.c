#include "minishell.h"

void	my_exit(char **args)
{
	int		ac;

	ac = 0;
	while (args[ac])
		ac++;
	if (ac == 1)
		exit(0);
	else if (ac > 1 && !is_str_digit(args[1]))
		exit_not_digit(args[1]);
	else if (ac == 2)
		exit(ft_atoi(args[1]));
	else
		exit_many_args();
}
