//Only malloc the command line
#include "minishell.h"

int		search_prog(char *prog_path, char **args, char **envp)
{
	char	**env_paths;
	char	path[PATH_MAX];
	int		i;
	int		ret;//can do without it

	env_paths = get_all_env_path(get_env_path(envp));
	if (!env_paths)
		return (0);//naze
	i = -1;
	ret = -1;
	while (env_paths[++i])
	{
		append_path_nomalloc(env_paths[i], args[0], path);
		if (!access(path, F_OK))
			ret = access(path, F_OK);
		if (ret == 0)//0 is good
		{
			prog_path = ft_strcpy(prog_path, path);
			return (1);
		}
	}
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

void	get_right_cmd(char **args, char **envp)
{
	int		pid;
	int		test;
	char	prog_path[PATH_MAX];//pas sure

	if (check_built_in(args, envp))//if else might be better
		return ;
	printf("built_in not found\n");
	//search_prog should return 1 if found, 0 otherwise
	//and set prog_path
	printf("args[0]: %s\nargs[1]: %s\n", args[0], args[1]);
	//if args start with a '/', i shouldn't use search_prog()
	if (search_prog(prog_path, args, envp))
		my_exec(prog_path, args, envp);
	else
		cmd_not_found(args[0]);
}

//chemin a chier
void	get_cmd_args(char *line, char **envp)
{
	char	**args;

	args = ft_strsplit(line, ' ');
	get_right_cmd(args, envp);
}

int		loop(char **envp)
{
	//char	buf[ARG_MAX];//ARG_MAX est trop grand
	char	*buf;
	char	c;
	int		i;
	int		ret;

	buf = ft_strnew(BUF_SIZE);
	ft_bzero(buf, BUF_SIZE);
	i = 0;
	ret = 0;
	print_prompt();
	while ((ret = read(1, &c, 1)))
	{
		if (ret == -1)
			ERROR_READ;
		if (c == 10)
		{
			if (*buf)
				get_cmd_args(buf, envp);
			reset_buf(buf, &i);
			print_prompt();
		}
		buf[i++] = c;
		//continue ;//useless !!
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = cpy_envp(envp);
	if (my_env && envp)
	{
		ft_putendl(envp[0]);
		ft_putendl(my_env[0]);
		ft_put_nultab(my_env);
		ft_putstr(my_env[0]);
	}
	loop(my_env);
	return (0);
}
