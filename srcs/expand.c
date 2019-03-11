/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:59:40 by penzo             #+#    #+#             */
/*   Updated: 2019/03/11 20:52:06 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_memdel((void*)&arg);
		return (NULL);
	}
	home_str = get_line_from_env("HOME", env);
	tilde_len = ft_strlen(home_str);
	if (!(new = ft_strnew(len + tilde_len)))
		ERROR_MEM;
	ft_strcpy(new, home_str);
	ft_strcpy(&new[tilde_len], &arg[1]);
	ft_memdel((void*)&arg);
	return (new);
}

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
			if (!(tmp = get_var_name(&arg[i])))
			{
				ft_memdel((void*)&arg);
				return (0);
			}
			if (!(get_line_from_env(tmp, env)))
				return (check_dollars_undefined(arg, tmp));
			malloc_len += ft_strlen(get_line_from_env(tmp, env));
			malloc_len -= ft_strlen(tmp) + 1;
			ft_memdel((void*)&tmp);
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
	ft_memdel((void*)&var_name);
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
	set_i_j(&i, -1, &j, 0);
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
	ft_memdel((void*)&arg);
	return (new);
}

int			expand_vars(char **args, char **env)
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
