/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaelle <gaelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:20:45 by gaelle            #+#    #+#             */
/*   Updated: 2023/10/23 20:19:51 by gaelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		len;
	int		i;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	len++;
	duplicate = (char *)malloc(len);
	if (!duplicate)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

/*int	main(void)
{
	char	original[] = "Bonjour correcteur !";
	char	*copy = ft_strdup(original);

	if (copy)
	{
		printf("Copie : %s\n", copy);
		free(copy);
	}
	else
	{
		printf("Echec allocation memoire\n");
	}
	return (0);
}*/
