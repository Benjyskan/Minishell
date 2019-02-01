#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>//tejme

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/syslimits.h>
# include "libft.h"
# define BUF_SIZE 124 //TODO
# define SHELL_NAME "my_sh"
# define HOME "/Users/penzo" //Degueu
# define ERROR_MEM exit(1) //naze
# define ERROR_READ exit(1) //naze
# define ERROR_EXEC exit(1) //naze
# define ERROR_FORK exit(1) //naze
# define ERROR_ENV exit(1) //naze

typedef struct	s_myenv //TODO a SHLVL var too
{
	char		**envp;
	char		home[PATH_MAX];
	char		pwd[PATH_MAX];
	char		old_pwd[PATH_MAX];
}				t_myenv;

/*
** built_in.c
*/

int				check_built_in(char **args, char **env);

/*
** cd.c
*/

void			cd_not_found(char **args, char **env);
int				my_cd(char **args, char **env);

/*
** str_utils.c
*/

int				is_str_digit(char *str);
void			reset_buf(char *buf, int *i);
void			append_path_nomalloc(char *env_path, char *prog_name,
		char *result);
int				get_ntab_len(char **tab);

/*
** msg.c
*/

void			cmd_not_found(char *prog_name);

/*
** exits.c
*/

void			exit_not_digit(char **args, char **env);
void			exit_many_args(void);
void			exit_numeric(char **args, char **env);

/*
** env_utils.c
*/

int				init_env(char **envp, t_myenv *my_env);
char			*get_line_from_env(char *search, char **env);
char			**get_all_env_path(char *path);
char			**cpy_envp(char **envp);

/*
** prompt.c
*/

void			print_prompt(void);

/*
** free.c
*/

void			free_nultab(char **tab);
#endif
