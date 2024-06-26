/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:20:45 by gaelle            #+#    #+#             */
/*   Updated: 2024/06/26 20:29:54 by gabarnou         ###   ########.fr       */
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
		ft_printf("Copie : %s\n", copy);
		free(copy);
	}
	else
	{
		ft_printf("Echec allocation memoire\n");
	}
	return (0);
}*/
