#include "minishell.h"

/*void	cd_not_found(char **args, char **env)
{
	(void)env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
}*/

void	cd_not_found_str(char *str)//clearer than the first one ?
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	cd_permi_denied(char **args, char **env)
{
	(void)env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": Permission denied", 2);
}

void	cd_invalid_option(char **args, t_myenv *my_env)
{
	(void)my_env;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(" invalid option", 2);
	ft_putendl_fd("cd: usage: cd [dir]", 2);
}
