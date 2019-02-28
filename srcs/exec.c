/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:48:19 by penzo             #+#    #+#             */
/*   Updated: 2019/02/28 11:48:23 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cycle_through_prog_paths(char *prog_path, char **env_paths,
			char *prog_name)
{
	int		i;
	char	path[PATH_MAX];

	i = -1;
	while (env_paths[++i])
	{
		append_path_nomalloc(env_paths[i], prog_name, path);
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
			{
				prog_path = ft_strcpy(prog_path, path);
				free_nultab(env_paths);
				return (1);
			}
			else if (access(path, X_OK))
			{
				exec_permission_denied(path);
				free_nultab(env_paths);
				return (-1);
			}
		}
	}
	return (0);
}

static int	search_prog(char *prog_path, char **args, char **envp)
{
	char	**env_paths;

	if (!(env_paths = get_all_env_path(get_line_from_env("PATH", envp)))
			|| (ft_strlen(get_line_from_env("PATH", envp)) == 0))
		replace_path_with_cwd(&env_paths);
	if (cycle_through_prog_paths(prog_path, env_paths, args[0]))
		return (1);
	free_nultab(env_paths);
	return (0);
}

static void	my_exec(char *prog_path, char **args, char **envp)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(prog_path, args, envp) == -1)
			ERROR_EXEC;
	}
	else if (pid > 0)
		wait(&pid);
	else if (pid < 0)
		ERROR_FORK;
}

static void	get_right_cmd(char **args, t_myenv *my_env)
{
	char	prog_path[PATH_MAX];

	if (ft_is_c_in_str(args[0], '/'))
	{
		if (!access(args[0], F_OK))
		{
			if (!access(args[0], X_OK))
				my_exec(args[0], args, my_env->envp);
		}
		else
			cmd_not_found(args[0]);
		free_nultab(args);
		return ;
	}
	if (check_built_in(args, my_env))
	{
		free_nultab(args);
		return ;
	}
	if (search_prog(prog_path, args, my_env->envp))
		my_exec(prog_path, args, my_env->envp);
	else
		cmd_not_found(args[0]);
	free_nultab(args);
}

void		get_cmd_args(char *line, t_myenv *my_env)
{
	char	**args;

	if (!(args = strsplit_multi(line, " \t")))
		ERROR_MEM;
	if (!*args)
	{
		free(args);
		return ;
	}
	if (!(expand_vars(args, my_env->envp)))
	{
		free_nultab(args);
		return ;
	}
	get_right_cmd(args, my_env);
}
