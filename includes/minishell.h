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
# define ERROR_MEM exit(1) //naze
# define ERROR_READ exit(1) //naze
//# define ERROR_EXEC exit(1) //naze
# define ERROR_EXEC ft_putendl("SDFSDFSDF") //naze
# define ERROR_FORK exit(1) //naze
# define ERROR_ENV exit(1) //naze

typedef struct	s_myenv
{
	char		**envp;
	char		home[PATH_MAX];//useless ?
	char		pwd[PATH_MAX];//useless ?
	char		old_pwd[PATH_MAX];
}				t_myenv;

/*
** built_in.c
*/

int				check_built_in(char **args, t_myenv *my_env);

/*
** built_in_env.c
*/

void			my_env_function(char **args, char **env);

/*
** built_in_env_utils.c
*/

int				do_envvar_exist(char *what, char **envp);

/*
** built_in_echo.c
*/

void			my_echo(char **args, t_myenv *my_env);

/*
** cd.c
*/

int				my_cd(char **args, t_myenv *my_env);

/*
** cd_errors.c
*/

void			cd_not_found(char **args, char **env);
void			cd_not_found_str(char *str);
void			cd_permi_denied(char **args, char **env);
void			cd_invalid_option(char **args, t_myenv *my_env);

/*
** str_utils.c
*/

int				is_str_digit(char *str);
void			reset_buf(char *buf, int *i);
void			append_path_nomalloc(char *env_path, char *prog_name,
		char *result);
int				get_ntab_len(char **tab);
void			strjoin_equal_nomalloc(char *s1, char *s2, char *result);

/*
** msg.c
** msg2.c
*/

void			cmd_not_found(char *prog_name);
void			undefined_variable(char *var_name);
void			exec_permission_denied(char *prog_name);
void			var_must_begin_letter(char *prog_name);
void			var_is_not_alphanum(char *prog_name);
void			too_many_args(char *prog_name);

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
int				get_linenumber_from_env(char *search, char **env);
char			**get_all_env_path(char *path);
char			**cpy_envp(char **envp);
//void			add_env_var(char *new_var, char **envp);
char			**add_env_var(char *new_var, char **envp);
//int				strcmp_before_equal(char *search, char *env_line);

/*
** prompt.c
*/

void			print_prompt(void);

/*
** free.c
*/

void			free_nultab(char **tab);

/*
** shlvl.c
*/

void			set_shlvl(char ***envp);

/*
** built_in_setenv.c
*/

void			my_setenv(char **args, char ***env);
#endif
