/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:50:14 by penzo             #+#    #+#             */
/*   Updated: 2019/03/12 16:19:28 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_buf(char *buf, int *i, int *buf_len)
{
	*i = 0;
	ft_bzero(buf, *buf_len);
	*buf_len = BUF_SIZE;
}

void	init_loop(int *i, int *ret, int *buf_len)
{
	*i = 0;
	*ret = 0;
	*buf_len = BUF_SIZE;
}

void	set_i_j(int *i, int i_val, int *j, int j_val)
{
	*i = i_val;
	*j = j_val;
}

void	my_env_norm(char **cur_envcmd, t_myenv *tmp_env)
{
	if (exec_env(cur_envcmd, tmp_env, 0))
		print_env(NULL, tmp_env->envp);
	free_nultab(cur_envcmd);
}

/*
** return a malloced empty env
*/

char	**env_i_options(char **env)
{
	free_nultab(env);
	if (!(env = malloc(sizeof(char**) * 1)))
		ERROR_MEM;
	env[0] = NULL;
	return (env);
}
