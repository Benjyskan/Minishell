//TODO: increment SHLVL !!
//Only malloc the command line
#include "minishell.h"

int		search_prog(char *prog_path, char **args, char **envp)
{
	char	**env_paths;
	char	path[PATH_MAX];
	int		i;
	int		ret;//can do without it

	env_paths = get_all_env_path(get_line_from_env("PATH", envp));
	if (!env_paths)
		return (0);//get_all_env_path failed
	i = -1;
	ret = -1;
	while (env_paths[++i])
	{
		append_path_nomalloc(env_paths[i], args[0], path);
		//free tab env_path, ou free ligne par ligne ?
		if (!access(path, F_OK))
			ret = access(path, X_OK);//X_OK
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
	char	prog_path[PATH_MAX];//pas sure

	(void)pid;
	//TODO: Free when i exit(built_in)
	if (check_built_in(args, my_env.envp))//if else might be better
	{
		free_nultab(args);
		return ;//free args
	}
	//search_prog should return 1 if found, 0 otherwise
	//and set prog_path
	//if args start with a '/', i shouldn't use search_prog()
	if (search_prog(prog_path, args, my_env.envp))
		my_exec(prog_path, args, my_env.envp);
	else
		cmd_not_found(args[0]);
	//free args
	free_nultab(args);
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
	free_nultab(my_env.envp);
	ft_putendl_fd("exit", 2);//<C-d>
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
	loop(my_env);
	return (0);
}
