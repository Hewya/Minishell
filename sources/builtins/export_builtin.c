/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:21 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/18 17:47:02 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	env_modif(t_data *data, char *s)
{
	t_data		*tmp;
	int			i;
	char		*value;
	char		**new_env;

	i = 0;
	tmp = data;
	value = ft_strchr(s, '=');
	new_env = NULL;
	while (data->env[i])
		i++;
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
	{
		ft_printf("malloc failed\n");
		return (1);
	}
	i = search_in_env(s, tmp->env, (ft_strlen(s) - ft_strlen(value)));
	if (i == -1)
		new_env_modif(data, new_env, s);
	else
		data->env[i] = s;
	return (0);
}*/

int env_modif(t_data *data, char *s)
{
	t_data *tmp;
	int i;
	char *value;
	char **new_env;

	i = 0;
	tmp = data;
	value = ft_strchr(s, '=');
	new_env = NULL;
	while (data->env[i])
		i++;
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
	{
		ft_printf("malloc failed\n");
		return (1);
	}

	i = search_in_env(s, tmp->env, (ft_strlen(s) - ft_strlen(value)));
	if (i == -1)
	{
		if (new_env_modif(data, new_env, s) != 0)
		{
			free(new_env);
			return (1);
		}
	}
	else
	{
		free(data->env[i]);
		data->env[i] = ft_strdup(s);
	}
	return (0);
}

/*
int	env_surcharge(t_data *data, char *s)
{
	size_t	len;
	char	*value;
	int		key;
	char	*new_value;

	key = 0;
	value = ft_strchr(s, '=') + 1;
	len = (ft_strlen(s) - ft_strlen(value)) - 2;
	if (find_key(data, s, len, value) == 0)
	{
		new_value = malloc(ft_strlen(data->env[key]) + ft_strlen(value) + 1);
		if (!new_value)
		{
			ft_printf("malloc failed\n");
			return (1);
		}
		ft_strcpy(new_value, data->env[key]);
		ft_strcat(new_value, value);
		data->env[key] = new_value;
	}
	return (0);
}*/

int env_surcharge(t_data *data, char *s)
{
	size_t len;
	char *value;
	int key;
	char *new_value;

	key = 0;
	value = ft_strchr(s, '=') + 1;
	len = (ft_strlen(s) - ft_strlen(value)) - 2;

	if (find_key(data, s, len, value) == 0)
	{
		new_value = malloc(ft_strlen(data->env[key]) + ft_strlen(value) + 1);
		if (!new_value)
		{
			ft_printf("malloc failed\n");
			return (1);
		}
		ft_strcpy(new_value, data->env[key]);
		ft_strcat(new_value, value);
		free(data->env[key]);
		data->env[key] = new_value;
	}
	return (0);
}


int	export_perform(t_data *data, char **args)
{
	int	i;
	int	res;
	int	invalid;

	i = 1;
	res = 0;
	invalid = -1;
	while (args[i] != NULL)
	{
		if (valid_arg(args[i]) != 0)
		{
			invalid = i;
			errmsg_cmd("export", args[i], "No such file or directory", CMD_NOT_FOUND);
			res = 1;
		}
		if (valid_arg(args[i]) == 0
			&& ft_valid_surcharge(args[i]))
			res = env_surcharge(data, args[i]);
		else if ((valid_arg(args[i])) == 0)
			res = env_modif(data, args[i]);
		i++;
	}
	if (invalid > -1)
		return (1);
	return (res);
}

int	export_builtin(t_data *data, char **args)
{
	int	invalid;

	invalid = -1;
	if (args[1] == NULL)
		ft_printf("yeah go see the man brooo !\n");
	else
		invalid = export_perform(data, args);
	if (invalid > -1)
		return (1);
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
		"./a.out",
		"_hello=ahnon",
		"HELL=YO",
		"AIDEzMoi",
		"FUCK=YEAH",
		"FUCK+=OK",
		"AHOUI+=etoui",
		NULL
	};
    char *env[] = {
		"FUCK=HOLA",
		"PWD=ici",
		"HELL=OUI",
        "PATH=/usr/bin",
        "USER=test_user",
        NULL
    };

    data.env = env;
    data.cmd = &cmd;
    cmd.args = args;
    return (export_builtin(&data));
}*/
