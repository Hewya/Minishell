/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:43:44 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/26 00:05:52 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_command *command)
{
	if (!command->io_fds)
		return ;
	if (command->io_fds->fd_in != -1)
		close(command->io_fds->fd_in);
	if (command->io_fds->fd_out != -1)
		close(command->io_fds->fd_out);
}

void	close_pipes(t_command *command)
{
	while (command)
	{
		if (command && command->pipe_fd)
		{
			close(command->pipe_fd[0]);
			close(command->pipe_fd[1]);
		}
		command = command->next;
	}
}