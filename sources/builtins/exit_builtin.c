/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:52:19 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/25 19:49:02 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

exit [n]
provoque l'arrêt du programme shell avec un code de retour ($?) égal à n.
Si n n'est pas précisé, le code de retour fourni est celui de la dernière commande exécutée.
exit prend seulement des arguments de type entier compris entre 0 et 255 d'où :
long long	code2;
code2 = ft_atoi_exit(args[1], 0, &pbm); // atoi adapté à exit, qui renvoie un long long (voir tests en dessous)
g_status = code2 % 256;

*/

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

static int	get_exit_code(t_data *data, char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (data->last_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

bool	exit_alone(t_data *data)
{
	if (data->cmd)
		return (false);
	if (data->cmd->next || data->cmd->prev)
		return (true);
	return (false);
}


int exit_builtin(t_data *data, char **args)
{
	int		exit_code;
	bool	error;

	error = false;
	if (exit_alone(data) == false)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_code = data->last_exit_code;
	else
	{
		exit_code = get_exit_code(data, args[1], &error);
		if (error)
			exit_code = errmsg_cmd("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many arguments", 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
