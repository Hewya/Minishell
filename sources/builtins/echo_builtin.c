/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:45:57 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/29 17:38:56 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag(char *args)
{
	size_t	i;

	if (args == NULL)
		return (false);
	if (args[0] != '-')
		return (false);
	if (args[1] != 'n')
		return (false);
	i = 2;
	while (args[i])
	{
		if (args[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	print_args(char **args, bool flag_newline)
{
	size_t	i;

	i = 1;
	while (args[i] && is_flag(args[i]) == true)
		i++;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!flag_newline)
		ft_printf("\n");
}

int	echo_builtin(t_data *data, char **args)
{
	(void)data;
	print_args(args, is_flag(args[1]));
	return (0);
}
