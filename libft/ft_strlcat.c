/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaelle <gaelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:45:40 by gaelle            #+#    #+#             */
/*   Updated: 2023/10/25 13:43:39 by gaelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	index;
	size_t	i;

	dst_len = ft_strlen(dest);
	index = 0;
	while (dest[index])
		index++;
	i = 0;
	while (src[i] && (i + index + 1) < (size))
	{
		dest[index + i] = src[i];
		i++;
	}
	if (i < size)
		dest[index + i] = '\0';
	if (size <= dst_len)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + dst_len);
}
