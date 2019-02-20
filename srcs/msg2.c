#include "minishell.h"

void	too_many_args(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": Too many arguments.", 2);
}
