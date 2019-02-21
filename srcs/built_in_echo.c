#include "minishell.h"

/*
** return 0 and print error if one of the $args isn't found
** return 1 if everything is found
*/

static int	check_echo_line(char **args, t_myenv *my_env)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '$' && args[i][1] != 0)
		{
			if (!get_line_from_env(args[i] + 1, my_env->envp))
			{
				undefined_variable(args[i] + 1);
				return (0);
			}
		}
		else if (args[i][0] == '~' && args[i][1] == 0)
		{
			if (!get_line_from_env("HOME", my_env->envp))
			{
				ft_putendl_fd("No $home variable set.", 2);
				return (0);
			}
		}
	}
	return (1);
}

static void	output_echo_line(char **args, t_myenv *my_env)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (i != 1)
			ft_putchar_fd(' ', 1);
		if (args[i][0] == '$' && args[i][1] != 0)
			ft_putstr_fd(get_line_from_env(args[i] + 1, my_env->envp), 1);
		else if (args[i][0] == '~' && args[i][1] == 0)
			ft_putstr_fd(get_line_from_env("HOME", my_env->envp), 1);
		else
			ft_putstr_fd(args[i], 1);
	}
	ft_putchar_fd('\n', 1);
}

void	my_echo(char **args, t_myenv *my_env)
{
	if (!check_echo_line(args, my_env))
		return ;
	else
		output_echo_line(args, my_env);
}
