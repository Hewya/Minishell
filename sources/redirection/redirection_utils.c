/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:43:44 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/23 17:43:59 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_data *data)
{
	if (!data->cmd->io_fds)
		return ;
	if (data->cmd->io_fds->fd_in != -1)
		close(data->cmd->io_fds->fd_in);
	if (data->cmd->io_fds->fd_out != -1)
		close(data->cmd->io_fds->fd_out);
}