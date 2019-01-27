#include "minishell.h"

void	exit_not_digit(char *str)
{
	ft_putstr(SHELL_NAME);
	ft_putstr(": exit: ");
	ft_putstr(str);
	ft_putendl(": numeric argument required");
	exit(-1);
}

void	exit_many_args(void)
{
	ft_putstr(SHELL_NAME);
	ft_putstr(": exit: ");
	ft_putendl("too many arguments");
}
