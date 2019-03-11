/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:51:15 by penzo             #+#    #+#             */
/*   Updated: 2019/03/11 19:53:56 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_separators(char c, char *separators)
{
	int		i;

	i = -1;
	while (separators[++i])
	{
		if (c == separators[i])
			return (1);
	}
	return (0);
}

static int	count_words(char const *s, char *separators)
{
	int		in_word;
	int		i;
	int		count;

	in_word = 0;
	i = -1;
	count = 0;
	while (s[++i])
	{
		if (in_word == 0 && !is_separators(s[i], separators))
		{
			in_word = 1;
			count++;
		}
		if (in_word == 1 && is_separators(s[i], separators))
			in_word = 0;
	}
	return (count);
}

static int	get_wordlen(char const *s, char *separators)
{
	int		i;

	i = 0;
	while (s[i] && !is_separators(s[i], separators))
		i++;
	return (i);
}

static int	fill_tab(char **tab, char *s, char *separators)
{
	int		in_word;
	int		i;
	int		j;

	i = -1;
	j = 0;
	in_word = 0;
	while (s[++i])
	{
		if (in_word == 0 && !is_separators(s[i], separators))
		{
			in_word = 1;
			if (!(tab[j] = ft_strndup(&s[i], get_wordlen(&s[i], separators))))
			{
				ft_memdel((void*)&tab);
				return (0);
			}
			j++;
		}
		if (in_word == 1 && is_separators(s[i], separators))
			in_word = 0;
	}
	tab[j] = 0;
	return (1);
}

char		**strsplit_multi(char const *s, char *separators)
{
	char	**tab;

	if (!s || !separators)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*)
					* (count_words(s, separators) + 1))))
		return (NULL);
	if (!fill_tab(tab, (char*)s, separators))
		return (NULL);
	return (tab);
}
