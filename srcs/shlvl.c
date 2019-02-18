#include "minishell.h"

static int	ft_getnblen(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len = 1;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	create_shlvl(char **envp)
{
}
void	set_shlvl_to_one(char *shlvl, char **envp)
{
	
}

void	shlvl_plus_one(char *shlvl, char **envp)
{
	int		nb;
	int		line_index;
	int		shlvl_len;
	char	*tmp;

	nb = ft_atoi(shlvl);
	nb++;
	nb = (nb < 0) ? 0 : nb;
	line_index = get_linenumber_from_env("SHLVL", envp);
	shlvl_len = ft_getnblen(nb);
////////////////
	//ft_memdel((void*)&envp[line_index]);//naze: autant free, vu que je reuse le pointeu
	free(envp[line_index]);
	//ft_bzero(envp[line_index], 8);
////////////////
	if (!(envp[line_index] = ft_memalloc(7 + shlvl_len)))
		ERROR_MEM;
	ft_strcpy(envp[line_index], "SHLVL=");
	tmp = ft_itoa(nb);
	ft_strlcat(envp[line_index], tmp, 7 + shlvl_len);//protect??
	printf("!!!shlvl: {%s}!!!\n", envp[line_index]);
	free(tmp);
}

void	set_shlvl(char **envp)
{
	char	*shlvl;

	shlvl = get_line_from_env("SHLVL", envp);
	printf("!!!!!!!!!!my shlvl: {%s}\n", shlvl);
	if (!shlvl)//shlvl exit pas, so realloc all env
	{
		ft_putendl("Ce cas n'arrive pas (enfaite, si)");//AH! env -i HOME=/Users/penzo ./minishell
		add_env_var("SHLVL=1", envp);
	}
	else if (!*shlvl)//shlvl exit, mais empty, so realloc SHLVL line
	{
		ft_putendl("set to 1 pls");
	}
	else//normal
	{
		ft_putendl("+1 pls");
		shlvl_plus_one(shlvl, envp);
		ft_putendl("----------------shlvl.c---------------");
		ft_put_nultab(envp);
		ft_putendl("end-------------shlvl.c---------------");
	}
}
