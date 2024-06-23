/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:21 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/23 18:15:29 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
*/
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

int	find_key(t_data *data, char *s, size_t len)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], s, len) == 0 && data->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	env_modif(t_data *data, char *s)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = NULL;
	while (data->env[i])
		i++;
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
	{
		printf("malloc failed\n");
		return (1);
	}
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_env[i] = ft_strdup(s);
	if (!new_env[i])
	{
		printf("strdup failed\n");
		free(new_env);
		return (1);
	}
	new_env[i + 1] = NULL;
	// need to free ?
	data->env = new_env;
	return (0);
}

int	env_surcharge(t_data *data, char *s)
{
	size_t	len;
	char	*value;
	int		key;
	char	*new_value;

	value = ft_strchr(s, '=') + 1;
	len = (ft_strlen(s) - ft_strlen(value)) - 2;
	key = find_key(data, s, len);
	if (key == -1)
		env_modif(data, s);
	else
	{
		new_value = malloc(ft_strlen(data->env[key]) + ft_strlen(value) + 1);
		if (!new_value)
		{
			printf("malloc failed\n");
			return (1);
		}
		strcpy(new_value, data->env[key]);
		strcat(new_value, value);
		data->env[key] = new_value;
	}
	return (0);
}

int	export_builtin(t_data *data)
{
	int	i;
	int	res;
	int	invalid;

	i = 0;
	res = 0;
	invalid = -1;
	if (data->cmd->args == NULL)
		printf("yeah go see the man brooo !\n");
	else
	{
		while (data->cmd->args[i] != NULL)
		{
			if (valid_arg(data->cmd->args[i]) != 0)
			{
				invalid = i;
				printf("export: %s: not a valid identifier",
					data->cmd->args[i]);
			}
			else if (ft_valid_surcharge(data->cmd->args[i]))
				res = env_surcharge(data, data->cmd->args[i]);
			else
				res = env_modif(data, data->cmd->args[i]);
			i++;
		}
	}
	if (invalid > -1)
		return (1);
	// print_env(data->env);
	return (res);
}

/*
 * leaks
// a enlever: pour surchargement si la key existe pas : affiche le +
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data data;
	t_command cmd;
	char *args[] = {
		"FUCK+=ROAD",
		"FU=HEU",
		NULL
	};
	char *env[] = {
		"FUCK=YEAH",
		"PWD=ici",
		"PATH=/usr/bin",
		"USER=test_user",
		NULL
	};

	data.env = env;
	data.cmd = &cmd;

	cmd.args = args;

	return (export(&data));
}*/
