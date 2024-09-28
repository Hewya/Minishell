/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:31:01 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/28 16:56:45 by amassias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (var == NULL)
		return (NULL);
	value = NULL;
	if (var && var_exists(data, var) == 0)
	{
		if (token != NULL)
			token->var_exist = true;
		value = search_env_var(data, var);
	}
	else if (var && var[0] == '?')
		value = ft_itoa(data->last_exit_code);
	else if (var && var[0] == '$')
		value = ft_itoa(getpid());
	free_ptr(var);
	return (value);
}
