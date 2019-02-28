#include "minishell.h"

void	exit_not_digit(char **args, t_myenv *my_env)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_nultab(args);
	free_nultab(my_env->envp);
	ft_memdel((void*)&my_env->old_pwd);
	exit(-1);
}

void	exit_many_args(void)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putendl_fd("too many arguments", 2);
}

void	exit_numeric(char **args, t_myenv *my_env)
{
	int		save;

	save = ft_atoi(args[1]);
	ft_putendl_fd("exit", 2);
	free_nultab(args);
	free_nultab(my_env->envp);
	ft_memdel((void*)my_env->old_pwd);
	exit(save);
}
