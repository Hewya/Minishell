/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:57 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/29 17:39:05 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_data *data, char **args)
{
	int	i;
	int	index_to_remove;

	i = 1;
	index_to_remove = -1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i], "not a valid identifier", false);
		}
		else
		{
			index_to_remove = get_env_var_index(data->env, args[i]);
			if (index_to_remove != -1)
				remove_env_var(data, index_to_remove);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
