/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:23:47 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/23 17:28:47 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**alloc_new_env(t_data *data, int len)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = ft_calloc((len + 1), sizeof * new_env);
	if (!new_env)
		return (NULL);
	while (data->env[i] && i < len)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

bool	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = length_env(data->env);
		data->env = alloc_new_env(data, idx + 1);
		if (!data->env)
			return (false);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

bool	remove_env_var(t_data *data, int index)
{
	int	i;
	int	len;

	i = index;
	len = index;
	if (index > length_env(data->env))
		return (false);
	free_ptr(data->env[i]);
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		len++;
		i++;
	}
	data->env = alloc_new_env(data, len);
	if (!data->env)
		return (false);
	return (true);
}
