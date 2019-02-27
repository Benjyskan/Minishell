#include "minishell.h"

static char	*expand_tilde(char *arg, char **env)
{
	char	*new;
	int		len;
	int		tilde_len;
	char	*home_str;

	len = ft_strlen(arg) - 1;
	if (!get_line_from_env("HOME", env) || !(*get_line_from_env("HOME", env)))
	{
		ft_putendl_fd("No $home variable set.", 2);
		return (NULL);
	}
	home_str = get_line_from_env("HOME", env);
	tilde_len = ft_strlen(home_str);
	if (!(new = ft_strnew(len + tilde_len)))
		ERROR_MEM;
	ft_strcpy(new, home_str);
	ft_strcpy(&new[tilde_len], &arg[1]);
	free(arg);
	return (new);
}

static char	*get_var_name(char *needle)
{
	int		i;
	char	*var_name;

	i = 1;
	while (ft_isalnum(needle[i]))
		i++;
	//if (i == 1)syntax error ?
	if (!(var_name = ft_strnew(i)))
		ERROR_MEM;
	ft_strncpy(var_name, &needle[1], i - 1);
	return (var_name);
}

//return total_len ? i do
static int	check_dollars(char *arg, char **env, int *ret)
{
	int		i;
	char	*tmp;
	int		malloc_len;

	i = -1;
	malloc_len = 0;
	while (arg[++i])
	{
		if (arg[i] == '$')
		{
			tmp = get_var_name(&arg[i]);//protect ?
			//ft_putendl(tmp);
			if (!(get_line_from_env(tmp, env)))
			{
				undefined_variable(tmp);
				free(tmp);//check
				free(arg);//test
				return (0);//output var does't exist
			}
			malloc_len += ft_strlen(get_line_from_env(tmp, env));
			malloc_len -= ft_strlen(tmp) + 1;
			free(tmp);
		}
	}
	*ret = malloc_len;
	return (1);
}

/*
** return size of expanded variable
*/

static int	expand_dollar(char *old, char *new, char **env)
{
	char	*var;
	char	*var_name;
	int		var_name_len;
	int		i;

	if (!(var_name = get_var_name(old)))
		ERROR_MEM;
	var = get_line_from_env(var_name, env);
	var_name_len = ft_strlen(var_name);
	free(var_name);
	i = -1;
	while (var[++i])
		new[i] = var[i];
	return (var_name_len);
}

static char	*expand_dollars(char *arg, char **env)
{
	char	*new;
	int		an_int;
	int		i;
	int		j;

	if (!(check_dollars(arg, env, &an_int)))
		return (NULL);
	an_int += ft_strlen(arg);
	if (!(new = ft_strnew(an_int)))
		ERROR_MEM;
	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] == '$')
		{
			an_int = expand_dollar(&arg[i], &new[j], env);
			i += an_int;
			while (new[j])
				j++;
		}
		else
			new[j++] = arg[i];
	}
	free(arg);
	return (new);
}

int		expand_vars(char **args, char **env)
{
	int		j;

	j = -1;
	while (args[++j])
	{
		if (args[j][0] == '~')
		{
			if (!(args[j] = expand_tilde(args[j], env)))
				return (0);
		}
		if (ft_is_c_in_str(args[j], '$'))
		{
			if (!(args[j] = expand_dollars(args[j], env)))
				return (0);
		}
	}
	return (1);
}
