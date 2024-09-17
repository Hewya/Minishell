/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:31:01 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/17 19:20:39 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  Checks if a variable exists in the environment list, returning 0
 * if it does and 1 if it doesn't.
 */
static int	var_exists(t_data *data, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Searches for an environment variable in the environment list and
 * returns a dynamically allocated string containing its value if found,
 * or NULL otherwise.
 */
static char	*search_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(data->env[i] + len);
	return (str);
}

char	*recover_value(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && var_exists(data, var) == 0)
	{
		if (token != NULL)
			token->var_exist = true;
		value = search_env_var(data, var);
	}
	else if (var && var[0] == '?')
		value = ft_itoa(data->last_exit_code);
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
