#ifndef MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# define BUF_SIZE 24 
# define SHELL_NAME "bensh"

/*
**	built_in.c
*/

void	my_exit(char **args);

/*
**	str_utils.c
*/

int		is_str_digit(char *str);

/*
**	exits.c
*/

void	exit_not_digit(char *str);
void	exit_many_args(void);
#endif
