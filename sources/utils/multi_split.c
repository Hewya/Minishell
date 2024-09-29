/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:24:41 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/29 17:36:56 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(void **tab)
{
	void	**itr;

	if (tab == NULL)
		return ;
	itr = tab;
	while (*itr)
		free(*itr++);
	free(tab);
}

static size_t	count_word(char const *s, const char *c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (ft_strchr(c, *s) == NULL
			&& (ft_strchr(c, s[1]) != NULL || s[1] == '\0'))
			++words;
		++s;
	}
	return (words);
}

static void	fill_tab(char *new, char const *s, const char *c)
{
	while (*s && ft_strchr(c, *s) == NULL)
		*new++ = *s++;
	*new = '\0';
}

static void	set_mem( char **tab, char const *s, const char *c)
{
	size_t	count;
	size_t	i;

	i = 0;
	while (*s)
	{
		count = 0;
		while (s[count] && ft_strchr(c, s[count]) == NULL)
			++count;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (tab[i] == NULL)
			{
				ft_free_tab((void **)tab);
				return ;
			}
			fill_tab(tab[i++], s, c);
			s += count - 1;
		}
		++s;
	}
	tab[i] = NULL;
}

char	**ft_multi_split(char const *s, const char *c)
{
	size_t	words;
	char	**tab;

	words = count_word(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem(tab, s, c);
	return (tab);
}
