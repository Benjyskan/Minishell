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
# define ERROR_EXEC exit(1) //naze
//# define ERROR_EXEC ft_putendl("Error exec (macro)") //naze
# define ERROR_FORK exit(1) //naze
# define ERROR_ENV exit(1) //naze

typedef struct	s_myenv
{
	char		**envp;
	char		*old_pwd;
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
void			strjoin_equal_nomalloc(char *s1, char *s2, char *result);
int				strcmp_before_equal(char *search, char *env_line);

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
void			too_few_args(char *prog_name);

/*
** exits.c
*/

void			exit_not_digit(char **args, t_myenv *my_env);
void			exit_many_args(void);
void			exit_numeric(char **args, t_myenv *my_env);

/*
** env_utils.c
*/

char			*get_line_from_env(char *search, char **env);
int				get_linenumber_from_env(char *search, char **env);
char			**get_all_env_path(char *path);
//void			add_env_var(char *new_var, char **envp);
char			**add_env_var(char *new_var, char **envp);

/*
** init_env.c
*/

void			init_env(char **envp, t_myenv *my_env);
//char			**cpy_envp(char **envp);

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

/*
** built_in_unsetenv.c
*/

int				count_args(char **args);
void			my_unsetenv(char **args, char ***env);

/*
** cmdline_utils.c
*/

int				expand_vars(char **args, char **env);

/*
** strsplit_multi.c
*/

char			**strsplit_multi(char const *s, char *separators);

/*
** expand.c
*/

int				expand_vars(char **args, char **env);

/*
** exec.c
*/

//void			my_exec(char *prog_path, char **args, char **envp);
//int				search_prog(char *prog_path, char **args, char **envp);
//void			get_right_cmd(char **args, t_myenv *my_env);
void			get_cmd_args(char *line, t_myenv *my_env);

/*
** minishell.c
*/

void			replace_path_with_cwd(char ***env_paths);
#endif
