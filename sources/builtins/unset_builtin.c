/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:57 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/24 19:12:12 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	here_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}*/

/*
void	_free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}*/

int	length_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
int	search_in_env(char *s, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(s, env[i], strlen(s)) == 0)
			return (i);
		i++;
	}
	return (-1);
}*/

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
		i++;
	}
	return (new_env);
}

void	remove_env_var(t_data *data, int index)
{
	int	i;
	int	len;

	i = index;
	len = index;
	if (index > length_env(data->env))
		return ;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		len++;
		i++;
	}
	data->env = alloc_new_env(data, len);
}

int	prep_unset(char **env, char *s)
{
	int	index_to_remove;

	index_to_remove = -1;
	if (ft_strchr(s, '=') != 0 || search_in_env(s, env, ft_strlen(s)) == -1)
		return (-1);
	index_to_remove = search_in_env(s, env, ft_strlen(s));
	return (index_to_remove);
}

int	unset_builtin(t_data *data)
{
	int	i;
	int	index_to_remove;

	i = 1;
	index_to_remove = -1;
	if (!data->env || !data->cmd->args[1])
		return (0);
	while (data->cmd->args[i])
	{
		index_to_remove = prep_unset(data->env, data->cmd->args[i]);
		if (index_to_remove != -1)
			remove_env_var(data, index_to_remove);
		i++;
	}
	//here_print_env(data->env);
	return (0);
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
		printf("Unset function executed successfully.\n");
	else
		printf("Unset function failed.\n");
	return (0);
}*/
