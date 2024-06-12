/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:33:01 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/12 20:14:50 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_join(char const *s1, char const *s2, int freed)
{
	if (freed == 3)
	{
		free((char *)s1);
		free((char *)s2);
	}
	else if (freed == 2)
		free((char *)s2);
	else if (freed == 1)
		free((char *)s1);
	else
		return ;
}
/**
 * @brief Joins two strings, freeing on demand, and returns the resulting
 * concatenated string.
 * To free the first string, int i needs to be equal to 1.
 * To free the second string, int i needs to be equal to 2.
 * To free both, int i needs to be equal to 3.
*/
char	*ft_strjoin_free(char const *s1, char const *s2, int i)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	free_join(s1, s2, i);
	return (result);
}
