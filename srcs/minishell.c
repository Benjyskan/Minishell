//Only malloc the command line
#include "minishell.h"

int		search_prog(char *prog_path, char **args, char **envp)
{
	char	**env_paths;
	char	path[PATH_MAX];
	int		i;
	int		ret;//can do without it

	env_paths = get_all_env_path(get_env_path(envp));
	//env_paths = get_all_env_path(get_line_from_env("PATH", envp));
	printf("path[0]: {%s}\n", env_paths[0]);
	printf("path[1]: {%s}\n", env_paths[1]);
	printf("path[2]: {%s}\n", env_paths[2]);
	if (!env_paths)
		return (0);//get_all_env_path failed
	i = -1;
	ret = -1;
	while (env_paths[++i])
	{
		append_path_nomalloc(env_paths[i], args[0], path);
		//free tab env_path, ou free ligne par ligne ?
		if (!access(path, F_OK))
			ret = access(path, F_OK);//X_OK
		if (ret == 0)//0 is good
		{
			prog_path = ft_strcpy(prog_path, path);
			//free ici
			return (1);
		}
	}
	//free ici
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
	}
	else if (pid > 0)
		wait(&pid);
	else if (pid < 0)
		ERROR_FORK;
}

void	get_right_cmd(char **args, t_myenv my_env)
{
	int		pid;
	int		test;
	char	prog_path[PATH_MAX];//pas sure

	if (check_built_in(args, my_env.envp))//if else might be better
		return ;//free args
	printf("built_in not found\n");
	//search_prog should return 1 if found, 0 otherwise
	//and set prog_path
	printf("args[0]: %s\nargs[1]: %s\n", args[0], args[1]);
	//if args start with a '/', i shouldn't use search_prog()
	if (search_prog(prog_path, args, my_env.envp))
		my_exec(prog_path, args, my_env.envp);
	else
		cmd_not_found(args[0]);
	//free args
}

//chemin a chier
void	get_cmd_args(char *line, t_myenv my_env)
{
	char	**args;

	args = ft_strsplit(line, ' ');
	get_right_cmd(args, my_env);
}

int		loop(t_myenv my_env)
{
	char	*buf;
	char	c;
	int		i;
	int		ret;

	buf = ft_strnew(BUF_SIZE);
	i = 0;
	ret = 0;
	print_prompt();
	while ((ret = read(1, &c, 1)))
	{
		if (ret == -1)//when do i go in ?
			ERROR_READ;
		if (c == 10)
		{
			if (*buf)
				get_cmd_args(buf, my_env);
			reset_buf(buf, &i);
			print_prompt();
		}
		buf[i++] = c;
	}
	ft_putendl_fd("exit", 2);//<C-d>
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_myenv	my_env;

	(void)argc;
	(void)argv;
	if (!init_env(envp, &my_env))
		ERROR_ENV;
	if (my_env.envp)
	{
		//printf("real env[0]: %s\n", envp[0]);
		//printf("my env[0]: %s\n", my_env.envp[0]);
		ft_put_nultab(my_env.envp);
		//ft_put_nultab(envp);
	}
	loop(my_env);
	return (0);
}
