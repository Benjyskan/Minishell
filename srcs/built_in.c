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
		//exit_not_digit(args[1]);
		exit_not_digit(args, env);
	}
	else if (ac == 2)
		exit_numeric(args, env);
	else
		exit_many_args();
}

int		my_echo(char **args, char **env)
{
	(void)args;
	(void)env;
	printf("WEHEY ECHO\n");
	return (0);
}


/*
** return 1 if prog_name is a built_in
** return 0 otherwise
** maybe useless ?
*/

int		check_built_in(char **args, char **env)
{
	int		ret;

	ret = 1;
	if ((ft_strcmp(args[0], "exit")) == 0)
		my_exit(args, env);
	else if ((ft_strcmp(args[0], "echo")) == 0)
		my_echo(args, env);
	else if ((ft_strcmp(args[0], "cd")) == 0)
		my_cd(args, env);
	else
		ret = 0;
	return (ret);
}
