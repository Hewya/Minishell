/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:57 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/26 20:29:54 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	here_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}*/

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
/*
int main(int argc, char **argv)
{
	t_data data;
	t_command cmd;
	char *args[] = {
		"",
		NULL
	};
	char *env[] = {
		"PATH=/usr/bin",
		"USER=test_user",
		"HELLO=world",
		"FUCK=YEAK",
		"RHO=MM",
		NULL
	};

	data.env = env;
	data.cmd = &cmd;

	cmd.args = args;


	if (unset_builtin(&data) == 0)
		ft_printf("Unset function executed successfully.\n");
	else
		ft_printf("Unset function failed.\n");
	return (0);
}*/
