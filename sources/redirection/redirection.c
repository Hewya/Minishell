/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:53:06 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/29 17:39:34 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	io_fd_handler(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	return (ret);
}

bool	io_fd_restore(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

bool	pipes_handler(t_command *cmds, t_command *command)
{
	if (!command)
		return (false);
	if (command->prev && command->prev->pipe_output)
	{
		if (dup2(command->prev->pipe_fd[0], STDIN_FILENO) == -1)
			return (errmsg_cmd("dup2", "pipe_fd[0]", strerror(errno), false));
		close(command->prev->pipe_fd[0]);
	}
	if (command->pipe_output)
	{
		if (dup2(command->pipe_fd[1], STDOUT_FILENO) == -1)
			return (errmsg_cmd("dup2", "pipe_fd[1]", strerror(errno), false));
		close(command->pipe_fd[1]);
	}
	close_pipes(cmds, command);
	return (true);
}

bool	create_pipes(t_data *data)
{
	t_command	*cmd;
	int			*fd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->pipe_output || (cmd->prev && cmd->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				perror("create pipes failed\n");
				free(fd);
				close_pipes(data->cmd, NULL);
				free_data(data, false);
				return (false);
			}
			cmd->pipe_fd = fd;
		}
		cmd = cmd->next;
	}
	return (true);
}
