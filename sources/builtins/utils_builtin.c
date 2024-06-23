/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:39:05 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/21 14:39:38 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_surcharge(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		return (false);
	while (s[i] && s[i + 1])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (true);
		i++;
	}
	return (false);
}
