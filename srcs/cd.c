#include "minishell.h"

void	cd_not_found(char **args, char **env)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
}

/*
** cd -: cd to OLD_PWD
** cd : cd to ~
** cd return 0 if succesfull
** cd return 1 if it fail
**
** cd reset PWD and OLDPWD even if they don4t exist anymore
*/

int		my_cd(char **args, char **env)
{
	if (!args[1])
	{
		if (chdir("~") == -1)//find HOME in env
			printf("~\n");
		return (0);
	}
	else if (args[1])//bof
	{
		if (chdir(args[1]) == -1)
		{
			cd_not_found(args, env);
			return (1);
		}
		//else
		//	printf("%s\n", args[1]);
		return (0);
	}
	return (0);
}
