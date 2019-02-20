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

//do i use it ?
void			strjoin_equal_nomalloc(char *s1, char *s2, char *result)
{
	int		i;
	int		j;

	ft_bzero(result, PATH_MAX);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	result[i] = '=';
	j = -1;
	if (!s2)
		return ;
	while (s2[++j])
		result[++i] = s2[j];
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
	*i = 0;
	ft_bzero(buf, BUF_SIZE);	
}

//unsigned int	get_ntab_len(char **tab)//move to libft
int	get_ntab_len(char **tab)//move to libft
{
	//unsigned int	i;
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

