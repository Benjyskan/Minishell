/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:11:24 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 14:28:06 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_minienv(void)
{
	int		init_lines;
	char	**envp;
	char	pwd[PATH_MAX];

	init_lines = 3;
	if (!(envp = (char**)malloc(sizeof(char**) * init_lines)))
		ERROR_MEM;
	if (!(envp[0] = ft_strnew(7 + 8)))
		ERROR_MEM;
	ft_strcpy(envp[0], "SHLVL=1");
	getcwd(pwd, PATH_MAX);
	if (!(envp[1] = ft_strnew(4 + ft_strlen(pwd))))
		ERROR_MEM;
	ft_strcpy(envp[1], "PWD=");
	ft_strcpy(&envp[1][4], pwd);
	envp[init_lines - 1] = NULL;
	return (envp);
}

/*
** if envp: MALLOC
** else: return NULL or should i malloc a mini_env ? yes, which malloc too
*/

static char	**cpy_envp(char **envp)
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
	ft_bzero(my_env->old_pwd, PATH_MAX);
	if (*envp)
		my_env->envp = cpy_envp(envp);
	else
		my_env->envp = create_minienv();
	return ;
}
