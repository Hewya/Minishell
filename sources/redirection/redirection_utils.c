/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:43:44 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/28 14:40:48 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_command *command, bool close_back)
{
	if (command->io_fds)
	{
		if (command->io_fds->fd_in != -1)
			close(command->io_fds->fd_in);
		if (command->io_fds->fd_out != -1)
			close(command->io_fds->fd_out);
		if (close_back)
			io_fd_restore(command->io_fds);
	}
	close_pipes(command, NULL);
}

void	close_pipes(t_command *command, t_command *skip_cmd)
{
	while (command)
	{
		if (command != skip_cmd && command->pipe_fd)
		{
			close(command->pipe_fd[0]);
			close(command->pipe_fd[1]);
		}
		command = command->next;
	}
}
