/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:09:17 by penzo             #+#    #+#             */
/*   Updated: 2019/03/13 18:09:24 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/syslimits.h>
# include "libft.h"
# define BUF_SIZE 2
# define SHELL_NAME "my_sh"
# define ERROR_MEM exit(1)
# define ERROR_READ exit(1)
# define ERROR_EXEC exit(1)
# define ERROR_FORK exit(1)
# define ERROR_ENV exit(1)

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

void			my_env_function(char **args, t_myenv *my_env);
int				exec_env(char **short_cmd, t_myenv *tmp_env, int mod);

/*
** built_in_env_utils.c
*/

int				do_envvar_exist(char *what, char **envp);
void			print_env(char **args, char **env);
char			**dup_env(char **env);
int				is_no_cmd_left(char **args);
int				is_valid_options(char *arg);
int				is_last_cmd(char **args);

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

void			cd_not_found_str(char *str);
void			cd_permi_denied(char **args, char **env);
void			cd_invalid_option(char **args, t_myenv *my_env);
void			cd_not_found_str_free(char *str, char *to_free);

/*
** str_utils.c
*/

int				is_str_digit(char *str);
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
void			print_env_usage(char c);
void			file_name_too_long(char *file_name);

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
char			**add_env_var(char *new_var, char **envp);
char			**replace_env_var(char *new_line, int index, char **env);

/*
** init_env.c
*/

void			init_env(char **envp, t_myenv *my_env);
char			**cpy_envp(char **envp);

/*
** prompt.c
*/

void			print_prompt(void);

/*
** free.c
*/

void			free_nultab(char **tab);
void			free_double_nultab(char **tab1, char **tab2);
int				free_nultab_ret_int(char **tab, int ret);
void			free_env_and_nultab(t_myenv *my_env, char **tab);

/*
** shlvl.c
*/

void			set_shlvl(char ***envp);

/*
** built_in_setenv.c
*/

void			my_setenv(char **args, t_myenv *my_env);

/*
** built_in_unsetenv.c
*/

int				count_args(char **args);
void			my_unsetenv(char **args, char ***env);

/*
** cmdline_utils.c
*/

int				expand_vars(char **args, char **env);
void			transform_cmdline(char *line, t_myenv *my_env);
void			fill_buf(char **buf, int *i, char c, int *buf_len);

/*
** strsplit_multi.c
*/

char			**strsplit_multi(char const *s, char *separators);

/*
** expand.c
*/

int				expand_vars(char **args, char **env);
char			*get_var_name(char *needle);
int				check_dollars_undefined(char *arg, char *tmp);

/*
** exec.c
*/

void			env_exec(char **args, t_myenv *my_env);
void			get_right_prog(char **args, t_myenv *my_env);

/*
** minishell.c
*/

void			replace_path_with_cwd(char ***env_paths);

/*
** for_the_norm.c
*/

void			reset_buf(char *buf, int *i, int *buf_len);
void			init_loop(int *i, int *ret, int *buf_len);
void			set_i_j(int *i, int i_val, int *j, int j_val);
void			my_env_norm(char **cur_envcmd, t_myenv *tmp_env);
char			**env_i_options(char **env);
#endif
