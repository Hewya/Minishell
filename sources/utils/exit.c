/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:05:31 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/29 17:39:44 by echapuis         ###   ########.fr       */
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
