/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaelle <gaelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:21:59 by gaelle            #+#    #+#             */
/*   Updated: 2023/10/25 12:13:34 by gaelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reverse_copy(char *d, const char *s, size_t n)
{
	s = s + n;
	d = d + n;
	while (n > 0)
	{
		d--;
		s--;
		*d = *s;
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (d == s)
	{
		return (dest);
	}
	if (s < d && s + n > d)
	{
		reverse_copy(d, s, n);
	}
	else
	{
		while (n > 0)
		{
			*d = *s;
			d++;
			s++;
			n--;
		}
	}
	return (dest);
}
