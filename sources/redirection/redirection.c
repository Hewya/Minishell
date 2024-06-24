/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:53:06 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/24 17:54:22 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	io_fd_handler(t_io_fds *io_fds)
{
	if (io_fds && io_fds->fd_in != -1)
	{
		io_fds->stdin_backup = dup(STDIN_FILENO);
		if (dup2(io_fds->fd_in, STDIN_FILENO) == -1 || io_fds->stdin_backup ==
			-1)
		{
			ft_putendl_fd("error io_fd_handler", 2);
			// free ?
			return (1);
		}
	}
	if (io_fds && io_fds->fd_out != -1)
	{
		io_fds->stdout_backup = dup(STDOUT_FILENO);
		if (dup2(io_fds->fd_out, STDOUT_FILENO) == -1 || io_fds->fd_out == -1)
		{
			ft_putendl_fd("error io_fd_handler", 2);
			// free ?
			return (1);
		}
	}
	return (0);
}

int	io_fd_restore(t_io_fds *io_fds)
{
	int	res;

	res = SUCCESS;
	if (io_fds && io_fds->stdin_backup != -1)
	{
		if (dup2(io_fds->stdin_backup, STDIN_FILENO) == -1)
			res = FAILURE;
		close(io_fds->stdin_backup);
		io_fds->stdin_backup = -1;
	}
	if (io_fds && io_fds->stdout_backup != -1)
	{
		if (dup2(io_fds->stdout_backup, STDOUT_FILENO) == -1)
			res = FAILURE;
		close(io_fds->stdout_backup);
		io_fds->stdout_backup = -1;
	}
	return (res);
}

void	close_pipes(t_data *data)
{
	t_data	*tmp;

	tmp = data;
	while (tmp->cmd)
	{
		if (tmp->cmd && tmp->cmd->pipe_fd)
		{
			close(tmp->cmd->pipe_fd[0]);
			close(tmp->cmd->pipe_fd[1]);
		}
		tmp->cmd = tmp->cmd->next;
	}
}

int	pipes_handler(t_data *data)
{
	int			res;
	t_command	*command;

	res = SUCCESS;
	command = data->cmd;
	if (command && command->pipe_output)
		if (dup2(command->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			ft_putendl_fd("error pipes handler fd[1]", 2);
			res = FAILURE;
		}
	if (command && command->prev && command->prev->pipe_output)
		if (dup2(command->pipe_fd[0], STDIN_FILENO) == -1)
		{
			ft_putendl_fd("error pipes handler fd[0]", 2);
			res = FAILURE;
		}
	if (!command)
		res = FAILURE;
	return (res);
}

int	create_pipes(t_data *data)
{
	t_command	*cmd;
	int			*fd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->next != NULL && cmd->pipe_output)
		{
			fd = malloc(2 * sizeof(int));
			if (!fd || pipe(fd) == -1)
			{
				perror("create pipes failed\n");
				// free data
				// exit
			}
			cmd->pipe_fd = fd;
		}
		cmd = cmd->next;
	}
	return (0);
}
