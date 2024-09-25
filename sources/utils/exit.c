/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:05:31 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/25 23:45:52 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (!data->cmd)
			dprintf(STDERR_FILENO, "exit\n");
		if (data->cmd && data->cmd->io_fds)
			close_fd(data->cmd, true);
		free_data(data, true);
		rl_clear_history();
	}
	exit(exno);
}
