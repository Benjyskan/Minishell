#include "minishell.h"

void	exit_not_digit(char *str)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(-1);
}

void	exit_many_args(void)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putendl_fd("too many arguments", 2);
}
