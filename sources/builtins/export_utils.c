/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:06:05 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/26 20:29:54 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_valid_surcharge(char *s)
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

int	valid_arg(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i]))
		return (1);
	if (!ft_isalnum(s[i]))
	{
		if (s[i] != '_')
			return (1);
	}
	if (!ft_strchr(s, '='))
		return (1);
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] != '=')
			return (1);
		else if (!(ft_isalnum(s[i])) && s[i] != '_' && s[i] != '='
			&& s[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

/*
int	find_key( t_data *data, char *s, size_t len, char *value)
{
	char	*final_key;
	bool	key_status;
	int		i;

	i = 0;
	final_key = NULL;
	key_status = false;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], s, len) == 0 && data->env[i][len] == '=')
			key_status = true;
		i++;
	}
	if (key_status == false)
	{
		final_key = ft_strndup(s, len);
		ft_strcat(final_key, "=");
		ft_strjoin(final_key, value);
		env_modif(data, ft_strjoin(final_key, value));
		return (1);
	}
	return (0);
}*/


// a diviser
int find_key(t_data *data, char *s, size_t len, char *value)
{
	char *new_entry;
	char *key_part;
	char *final_key;
	bool key_status;
	int i;

	i = 0;
	key_status = false;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], s, len) == 0 && data->env[i][len] == '=')
		{
			key_status = true;
			break;
		}
		i++;
	}
	if (!key_status)
	{
		key_part = ft_strndup(s, len);
		final_key = ft_strjoin(key_part, "=");

		if (final_key == NULL)
		{
			free(key_part);
			return (1);
		}
		new_entry = ft_strjoin(final_key, value);
		if (new_entry == NULL)
		{
			free(key_part);
			free(final_key);
			return (1);
		}
		env_modif(data, new_entry);
		free(key_part);
		free(final_key);
		free(new_entry);
		return (1);
	}
	return (0);
}



/*
int	new_env_modif(t_data *data, char **new_env, char *s)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_env[i] = ft_strdup(s);
	if (!new_env[i])
	{
		ft_printf("strdup failed\n");
		free(new_env);
		return (1);
	}
	new_env[i + 1] = NULL;
	data->env = new_env;
	return (0);
}*/

int new_env_modif(t_data *data, char **new_env, char *s)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_env[i] = ft_strdup(s);
	if (!new_env[i])
	{
		ft_printf("strdup failed\n");
		free(new_env);
		return (1);
	}
	new_env[i + 1] = NULL;
	free(data->env);
	data->env = new_env;
	return (0);
}

