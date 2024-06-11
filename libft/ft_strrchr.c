/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaelle <gaelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:56:24 by gaelle            #+#    #+#             */
/*   Updated: 2023/10/26 11:14:36 by gaelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s != NULL)
		i++;
	while (i >= 0)
	{
		if (s[i] == (const char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
