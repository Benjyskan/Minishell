#include "minishell.h"

int		search_prog(char *prog_path, char **args, char **envp)
{
	char	**env_paths;
	char	path[PATH_MAX];
	int		i;
	int		ret;//can do without it

	if (!(env_paths = get_all_env_path(get_line_from_env("PATH", envp)))
			|| (ft_strlen(get_line_from_env("PATH", envp)) == 0))
	{
		free_nultab(env_paths);
		env_paths = (char**)malloc(sizeof(char**) * 2);
		env_paths[0] = malloc(sizeof(char*) * PATH_MAX);
		env_paths[1] = NULL;
		getcwd(env_paths[0], PATH_MAX);
	}
	i = -1;
	ret = 1;
	while (env_paths[++i])
	{
		append_path_nomalloc(env_paths[i], args[0], path);
		if (!access(path, F_OK))
			ret = access(path, X_OK);
		if (ret == 0)//0 is good
		{
			prog_path = ft_strcpy(prog_path, path);
			free_nultab(env_paths);
			return (1);
		}
		else if (ret == -1)
		{
			exec_permission_denied(path);
			free_nultab(env_paths);
			return (-1);
		}
	}
	free_nultab(env_paths);
	return (0);
}

void	my_exec(char *prog_path, char **args, char **envp)
{
	int		pid;

	pid = fork();//when fork, check 3: child = 0, error < 0, parent > 0
	if (pid == 0)
	{
		if (execve(prog_path, args, envp) == -1)
			ERROR_EXEC;
		ft_putendl("OULALALALALA");//this will never happen
	}
	else if (pid > 0)
		wait(&pid);
	else if (pid < 0)
		ERROR_FORK;
}


void	get_right_cmd(char **args, t_myenv *my_env)
{
	int		pid;
	int		ret;
	char	prog_path[PATH_MAX];//pas sure

	(void)pid;
	//TODO: Free when i exit(built_in)
	if (ft_is_c_in_str(args[0], '/'))
	{
		//check if command exist
		if (!access(args[0], F_OK))
		{
			if(!access(args[0], X_OK))
				my_exec(args[0], args, my_env->envp);
		}
		else
			cmd_not_found(args[0]);
		free_nultab(args);
		return ;
	}
	if (check_built_in(args, my_env))//if else might be better
	{
		free_nultab(args);
		return ;
	}
	//search_prog should return 1 if found, 0 otherwise
	//and set prog_path
	ret = search_prog(prog_path, args, my_env->envp);
	if (ret == 1)
		my_exec(prog_path, args, my_env->envp);
	else if (ret == 0)
		cmd_not_found(args[0]);
	free_nultab(args);
}

//chemin a chier
void	get_cmd_args(char *line, t_myenv *my_env)
{
	char	**args;

	if (!(args = strsplit_multi(line, " \t")))//is it useless
		ERROR_MEM;
	if (!*args)
	{
		free(args);
		return ;
	}
	//expand here ?
	if (!(expand_vars(args, my_env->envp)))
	{
		free_nultab(args);
		return ;
	}
	get_right_cmd(args, my_env);
}

int		loop(t_myenv *my_env)
{
	char	*buf;
	char	c;
	int		i;
	int		ret;

	if (!(buf = ft_strnew(BUF_SIZE)))
		ERROR_MEM;
	i = 0;
	ret = 0;
	print_prompt();//check echo ls | ./minishell
	while ((ret = read(0, &c, 1)))
	{
		if (ret == -1)//when do i go in ?
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
	ft_memdel((void*)&buf);//pas sure
	free_nultab(my_env->envp);
	ft_putendl_fd("exit", 2);//<C-d> //check echo ls | ./minishell
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_myenv	my_env;

	(void)argc;
	(void)argv;
	if (!init_env(envp, &my_env))//for now, init never return 0
		ERROR_ENV;
	if (my_env.envp)
	{
		//printf("real env[0]: %s\n", envp[0]);
		//printf("my env[0]: %s\n", my_env.envp[0]);
		//ft_put_nultab(my_env.envp);
		//ft_put_nultab(envp);
	}
	loop(&my_env);
	return (0);
}
