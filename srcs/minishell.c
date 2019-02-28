/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:49:55 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 11:49:56 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_path_with_cwd(char ***env_paths)
{
	free_nultab(*env_paths);
	*env_paths = (char**)malloc(sizeof(char**) * 2);
	*env_paths[0] = malloc(sizeof(char*) * PATH_MAX);
	env_paths[0][1] = NULL;
	getcwd(*env_paths[0], PATH_MAX);
}

static void	exit_loop(char *buf, char **env)
{
	ft_memdel((void*)&buf);
	free_nultab(env);
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
	exit_loop(buf, my_env->envp);
}

int			main(int argc, char **argv, char **envp)
{
	t_myenv	my_env;

	(void)argc;
	(void)argv;
	init_env(envp, &my_env);//TODO return value ?
	loop(&my_env);
	return (0);
}
