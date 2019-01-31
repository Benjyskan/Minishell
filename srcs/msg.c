#include "minishell.h"

void	cmd_not_found(char *prog_name)
{
	ft_putstr(SHELL_NAME);
	ft_putstr(": ");
	ft_putstr(prog_name);
	ft_putendl(": command not found");
}
