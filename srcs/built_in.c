#include "minishell.h"

void	my_exit(char **args, char **env)
{
	int		ac;

	ac = 0;
	while (args[ac])
		ac++;
	if (ac == 1)
	{
		ft_putendl_fd("exit", 2);
		free_nultab(args);
		free_nultab(env);
		exit(0);
	}
	else if (ac > 1 && !is_str_digit(args[1]))
	{
		ft_putendl_fd("exit", 2);
		exit_not_digit(args, env);
	}
	else if (ac == 2)
		exit_numeric(args, env);
	else
		exit_many_args();
}

/*
** return 1 if prog_name is a built_in
** return 0 otherwise
** maybe useless ?
*/

int		check_built_in(char **args, t_myenv *my_env)
{
	if ((ft_strcmp(args[0], "exit")) == 0)
		my_exit(args, my_env->envp);
	else if ((ft_strcmp(args[0], "echo")) == 0)
		my_echo(args, my_env);
	else if ((ft_strcmp(args[0], "cd")) == 0)
		my_cd(args, my_env);
	else if ((ft_strcmp(args[0], "env")) == 0)
		my_env_function(args, my_env->envp);
	else if ((ft_strcmp(args[0], "setenv")) == 0)
		my_setenv(args, &my_env->envp);
	else if ((ft_strcmp(args[0], "unsetenv")) == 0)
		my_unsetenv(args, &my_env->envp);//&
	else
		return (0);
	return (1);
}
