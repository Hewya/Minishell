/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:21 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/26 00:56:21 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_arg(char *s)
{
	const char	*assign;
	size_t		i;

	assign = ft_strchr(s, '=');
	if (s[0] == '=')
		return (1);
	i = 0;
	if (ft_isalpha(s[i]) == 0 && s[i] != '_')
	{
		if (assign == NULL || assign[1] == '\0')
			return (1);
		else
			return (2);
	}
	i++;
	while (s[i] && s[i] != '=')
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
		{
			if (assign == NULL || assign[1] == '\0')
				return (1);
			else
				return (2);
		}
		i++;
	}
	return (0);
}

int	env_modif(t_data *data, char *s)
{
	char	**tab_pair;
	char	*val;

	tab_pair = malloc(sizeof * tab_pair * (2 + 1));
	if (tab_pair == NULL)
		return (2);
	val = ft_strchr(s, '=');
	if (val != NULL)
	{
		tab_pair[0] = ft_substr(s, 0, val - s);
		tab_pair[1] = ft_substr(val, 1, ft_strlen(val));
		tab_pair[2] = NULL;
	}
	else
	{
		tab_pair[0] = ft_substr(s, 0, val - s);
		tab_pair[1] = ft_strdup("");
		tab_pair[2] = NULL;
	}
	if (tab_pair[0] == NULL || tab_pair[1] == NULL)
		return (free(tab_pair[0]), free(tab_pair[1]), 1);
	set_env_var(data, tab_pair[0], tab_pair[1]);
	free_str_tab(tab_pair);
	return (0);
}

int	export_perform(t_data *data, char **args)
{
	int		i;
	int		res;
	int		code;

	i = 1;
	res = EXIT_SUCCESS;
	while (args[i] != NULL)
	{
		code = valid_arg(args[i]);
		if (code != 0)
		{
			printf("Failure on \"%s\"\n", args[i]);
			errmsg_cmd("export", args[i], "not a valid input",
				CMD_NOT_FOUND);
			res = code;
		}
		else
		{
			code = env_modif(data, args[i]);
			if (res == 0 && code)
				res = code;
		}
		i++;
	}
	return (res);
}

int	export_builtin(t_data *data, char **args)
{
	if (args[1] != NULL)
		return (export_perform(data, args));
	ft_printf("yeah go see the man brooo !\n");
	return (EXIT_SUCCESS);
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
