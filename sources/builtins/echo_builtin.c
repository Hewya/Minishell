/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:45:57 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/23 17:18:28 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag(char *args)
{
	int	i;

	i = 1;
	if (!(args[0] == '-' && args[i] == 'n'))
		return (false);
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
	int	i;

	i = 1;
	if (flag_newline)
		i++;
	while (args[i] && is_flag(args[i]) == true)
		i++;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (i >= 0 && args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!flag_newline)
		ft_printf("\n");
}

int	echo_builtin(t_data *data, char **args)
{
	int		i;
	bool	flag_newline;

	(void)data;
	i = 1;
	flag_newline = false;
	while (args[i])
	{
		if ((i != 1 && is_flag(args[i - 1]) == true
				&& is_flag(args[i]) == true)
			|| (i == 1 && is_flag(args[i]) == true))
		{
			flag_newline = true;
			break ;
		}
		i++;
	}
	print_args(args, flag_newline);
	return (0);
}
