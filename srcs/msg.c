#include "minishell.h"

void	cmd_not_found(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": command not found", 2);
}

void	undefined_variable(char *var_name)
{
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd(": Undefined variable.", 2);
}

void	exec_permission_denied(char *prog_name)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(": Permission denied", 2);
}
