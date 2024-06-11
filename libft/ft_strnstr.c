/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaelle <gaelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:10:11 by gaelle            #+#    #+#             */
/*   Updated: 2023/10/25 16:23:34 by gaelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	little_len = 0;
	while (little[little_len] != '\0')
		little_len++;
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i + little_len <= len)
	{
		j = 0;
		while (big[i + j] == little[j])
		{
			if (j == little_len - 1)
				return ((char *)(big + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
