/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:29:25 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/21 21:03:57 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_var_friendly(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int	var_length(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (len + 1);
	while (str[i])
	{
		if (is_var_friendly(str[i]) == false)
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*identify_var(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_var_friendly(str[i + 1]) == true)
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = var_length(str + start);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin_free(var, "=", 1);
	var = tmp;
	return (var);
}
