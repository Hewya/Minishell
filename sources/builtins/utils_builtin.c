/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:39:05 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/25 00:04:58 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_in_env(char *s, char **env, size_t len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(s, env[i], len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
