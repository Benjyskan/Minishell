#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr(SHELL_NAME);
	write(1, "> ", 2);
}
