/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:51:38 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/29 17:38:58 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_data *data)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = data;
	while (tmp->env[i])
	{
		if (ft_strchr(tmp->env[i], '='))
			ft_printf("%s\n", tmp->env[i]);
		i++;
	}
	return (0);
}

int	env_builtin(t_data *data, char **args)
{
	if (args[1] != NULL)
	{
		errmsg_cmd("env", args[1], "No such file or directory", false);
		return (127);
	}
	return (print_env(data));
}

/*
int main(int argc, char **argv)
{
	t_data data;
	t_command cmd;
	char *args[] = {
		"HEHO",
		NULL
	};
	char *env_path[] = {
		"PATH=/usr/bin",
		"USER=test_user",
		"HELLO=world",
		NULL
	};
	data.env = env_path;

	cmd.command = "env";
	cmd.args = args;
	data.cmd = &cmd;

	return (env(&data));
}*/
