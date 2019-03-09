/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:11:24 by penzo             #+#    #+#             */
/*   Updated: 2019/03/09 14:19:35 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_minienv(void)
{
	int		init_lines;
	char	**envp;
	char	*cwd;

	init_lines = 3;
	if (!(envp = (char**)malloc(sizeof(char**) * init_lines)))
		ERROR_MEM;
	if (!(envp[0] = ft_strnew(7 + 8)))
		ERROR_MEM;
	ft_strcpy(envp[0], "SHLVL=1");
	if (!(cwd = getcwd(NULL, 0)))
		ERROR_MEM;
	if (!(envp[1] = ft_strnew(4 + ft_strlen(cwd))))
		ERROR_MEM;
	ft_strcpy(envp[1], "PWD=");
	ft_strcpy(&envp[1][4], cwd);
	envp[init_lines - 1] = NULL;
	free(cwd);
	return (envp);
}

/*
** if envp: MALLOC
** else: return NULL or should i malloc a mini_env ? yes, which malloc too
*/

char		**cpy_envp(char **envp)
{
	int		tab_len;
	char	**my_env;
	int		i;

	tab_len = get_ntab_len(envp);
	if (!(my_env = (char**)malloc(sizeof(char**) * (tab_len + 1))))
		ERROR_MEM;
	my_env[tab_len] = NULL;
	i = -1;
	while (++i < (int)tab_len)
	{
		if (!(my_env[i] = ft_strdup(envp[i])))
			ERROR_MEM;
	}
	set_shlvl(&my_env);
	return (my_env);
}

/*
** set my_env via address
*/

void		init_env(char **envp, t_myenv *my_env)
{
	//ft_bzero(my_env->old_pwd, PATH_MAX);
	my_env->old_pwd = NULL;
	//TODO: modify old_pwd to char*, and free it when needed
	if (*envp)
	{
		my_env->envp = cpy_envp(envp);
		my_env->old_pwd = NULL;
	}
	else
		my_env->envp = create_minienv();
	return ;
}
