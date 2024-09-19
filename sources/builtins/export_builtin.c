/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:49:21 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/19 15:42:17 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_arg(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[i]) == 0 && s[i] != '_')
		return (1);
	i++;
	if (!ft_strchr(s, '='))
		return (1);
	while (s[i] != '=')
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	env_modif(t_data *data, char *s)
{
	char **tab_pair;
	char *val;

	val = ft_strchr(s, '=');
	tab_pair = malloc(sizeof * tab_pair * (2 + 1));
	tab_pair[0] = ft_substr(s, 0, val - s);
	tab_pair[1] = ft_substr(val, 1, ft_strlen(val));
	tab_pair[2] = NULL;
	set_env_var(data, tab_pair[0], tab_pair[1]);
	free_str_tab(tab_pair);
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
			errmsg_cmd("export", args[i], "not a valid identifier", CMD_NOT_FOUND);
			res = 1;
		}
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
