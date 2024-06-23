/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:57 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/21 15:07:02 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}*/
/*
void free_env(char **env)
{
	int i = 0;
	while (env[i])
		{
			free(env[i]);
			i++;
		}
	free(env);
}*/

bool init_unset_vars(t_data *data, char ***new_env, int *new_env_index)
{
	char **env;

	env = data->env;

	*new_env = malloc((length_env(env) + 1) * sizeof(char *));
	if (!*new_env) {
		perror("malloc failed");
		return (false);
	}
	*new_env_index = 0;
	return (true);
}

bool perform_unset(t_data *data, char **new_env, int *new_env_index)
{
	int i;
	int j;
	t_command *cmd;
	char **env;
	bool to_remove;

	i = 0;
	j = 0;
	to_remove = false;
	cmd = data->cmd;
	env = data->env;

	while (env[i])
	{
		while (cmd->args[j])
		{
			if (strncmp(env[i], cmd->args[j], strlen(cmd->args[j])) == 0 &&
				env[i][strlen(cmd->args[j])] == '=')
			{
				to_remove = true;
				break;
			}
			j++;
		}
		if (!to_remove)
		{
			new_env[*new_env_index] = strdup(env[i]);
			if (!new_env[*new_env_index])
			{
				perror("strdup failed");
				//free_env(new_env);
				return (false);
			}
			(*new_env_index)++;
		}
		i++;
	}
	new_env[*new_env_index] = NULL;
	return (true);
}


int unset_builtin(t_data *data)
{
	char **new_env;
	int new_env_index;

	if (!init_unset_vars(data, &new_env, &new_env_index))
		return (1);
	if (!perform_unset(data, new_env, &new_env_index))
		return (1);
	//free_env(data->env);
	data->env = new_env;
	//print_env(data->env);
	return (0);
}

/*
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data data;
	t_command cmd;
	char *args[] = {
		"PATH",
		NULL
	};
	char *env[] = {
		"PATH=/usr/bin",
		"USER=test_user",
		"HELLO=world",
		NULL
	};
	data.env = env;
	data.cmd = &cmd;

	cmd.args = args;
// pour tester rajouter print env,  dans unset car leak sinon pour affiche
	return (unset(&data));
}*/
