#include "minishell.h"

#include <stdio.h>
void	print_prompt(void)
{
	write(1, "$> ", 4);
}

void	get_right_cmd(char **args)
{
	//printf("%d\n", ft_strcmp(args[0], "exit"));
	if ((ft_strcmp(args[0], "exit")) == 0)
		my_exit(args);
}

void	get_cmd_args(char *line)
{
	char	**args;

	args = ft_strsplit(line, ' ');
	get_right_cmd(args);
}

void	reset_buf(char *buf, int *i)
{
	*i = 0;
	ft_bzero(buf, BUF_SIZE);	
}

int		loop(void)
{
	char	*buf;
	char	c;
	int		i;

	buf = ft_strnew(BUF_SIZE);
	ft_bzero(buf, BUF_SIZE);
	i = 0;
	print_prompt();
	while ((i += read(1, &c, 1)))
	{
		if (c == 10)
		{
			if (*buf)
				get_cmd_args(buf);
			reset_buf(buf, &i);
			print_prompt();
		}
		buf[i - 1] = c;
		continue ;
	}
	return (0);
}

int		main(void)
{
	loop();
	return (0);
}
