/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:24:41 by amassias          #+#    #+#             */
/*   Updated: 2024/09/28 18:49:00 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
size_t	_count_words(
			char const *s,
			const char *c
			);

static
void	_fill_tab(
			char *new,
			char const *s,
			const char *c
			);

static
void	_set_mem(
			char **tab,
			char const *s,
			const char *c
			);

void	ft_free_tab(
			void **tab
			)
{
	void	**itr;

	if (tab == NULL)
		return ;
	itr = tab;
	while (*itr)
		free(*itr++);
	free(tab);
}

char	**ft_multi_split(
			char const *s,
			const char *c
			)
{
	size_t	words;
	char	**tab;

	words = _count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	_set_mem(tab, s, c);
	return (tab);
}

static
size_t	_count_words(
			char const *s,
			const char *c
			)
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

static
void	_fill_tab(
			char *new,
			char const *s,
			const char *c
			)
{
	while (*s && ft_strchr(c, *s) == NULL)
		*new++ = *s++;
	*new = '\0';
}

static
void	_set_mem(
			char **tab,
			char const *s,
			const char *c
			)
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
			_fill_tab(tab[i++], s, c);
			s += count - 1;
		}
		++s;
	}
	tab[i] = NULL;
}
