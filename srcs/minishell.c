/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:49:55 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 19:16:37 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_path_with_cwd(char ***env_paths)
{
	free_nultab(*env_paths);
	*env_paths = (char**)malloc(sizeof(char**) * 2);
	env_paths[0][1] = NULL;
	if (!(*env_paths[0] = getcwd(NULL, 0)))
		ERROR_MEM;
}

/*
** exit_loop is called when <C-d>
*/

static void	exit_loop(char *buf, t_myenv *my_env)
{
	ft_memdel((void*)&buf);
	free_nultab(my_env->envp);
	ft_memdel((void*)&my_env->old_pwd);
	ft_putendl_fd("exit", 2);
}

static void	loop(t_myenv *my_env)
{
	char	*buf;
	char	c;
	int		i;
	int		ret;

	if (!(buf = ft_strnew(BUF_SIZE)))
		ERROR_MEM;
	i = 0;
	ret = 0;
	print_prompt();
	while ((ret = read(0, &c, 1)))
	{
		if (ret == -1)
			ERROR_READ;
		buf[i++] = c;
		if (c == 10)
		{
			buf[i - 1] = 0;
			if (*buf)
				get_cmd_args(buf, my_env);
			reset_buf(buf, &i);
			print_prompt();
		}
	}
	exit_loop(buf, my_env);
}

int			main(int argc, char **argv, char **envp)
{
	t_myenv	my_env;

	(void)argc;
	(void)argv;
	init_env(envp, &my_env);
	loop(&my_env);
	return (0);
}
