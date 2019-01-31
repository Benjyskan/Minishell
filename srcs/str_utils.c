#include "minishell.h"

int				is_str_digit(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
	}
	return (1);
}

void			append_path_nomalloc(char *env_path, char *prog_name, char *result)
{
	int		i;
	int		j;

	ft_bzero(result, PATH_MAX);
	i = -1;
	while (env_path[++i])
		result[i] = env_path[i];
	result[i] = '/';
	j = -1;
	while (prog_name[++j])
		result[++i] = prog_name[j];
}

void			reset_buf(char *buf, int *i)
{
	*i = -1;
	ft_bzero(buf, BUF_SIZE);	
}

unsigned int	get_ntab_len(char **tab)//move to libft
{
	unsigned int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

