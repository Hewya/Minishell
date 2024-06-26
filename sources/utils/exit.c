/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:05:31 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/26 00:06:58 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
		{
			close_fd(data->cmd);
			io_fd_restore(data->cmd->io_fds);
			close_pipes(data->cmd);
		}
		free_data(data, true);
	}
	exit(exno);
}
