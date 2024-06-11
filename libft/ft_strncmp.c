/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaelle <gaelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:04:51 by gaelle            #+#    #+#             */
/*   Updated: 2023/10/25 16:11:13 by gaelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	while (n > 0)
	{
		u1 = (unsigned char)*s1;
		u2 = (unsigned char)*s2;
		if (u1 != u2 || u1 == '\0' || u2 == '\0')
		{
			return ((int)(u1 - u2));
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}
