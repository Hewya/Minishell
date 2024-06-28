/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:52:45 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/28 14:46:33 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (data->cmd->command == NULL)
	{
		if (data->cmd->io_fds
			&& !check_infile_outfile(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

int	exec_builtins(t_data *data, t_command *cmd)
{
	int	res;

	res = CMD_NOT_FOUND;
	if (ft_strcmp(cmd->command, "cd") == 0)
		res = cd_builtin(data, cmd->args);
	else if (ft_strcmp(cmd->command, "echo") == 0)
		res = echo_builtin(data, cmd->args);
	else if (ft_strcmp(cmd->command, "env") == 0)
		res = env_builtin(data, cmd->args);
	else if (ft_strcmp(cmd->command, "export") == 0)
		res = export_builtin(data, cmd->args);
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		res = pwd_builtin();
	else if (ft_strcmp(cmd->command, "unset") == 0)
		res = unset_builtin(data, cmd->args);
	else if (ft_strcmp(cmd->command, "exit") == 0)
		res = exit_builtin(data, cmd->args);
	return (res);
}

int	exec_command(t_data *data, t_command *cmd)
{
	int	res;

	if (!cmd || !cmd->command)
		exit_shell(data, EXIT_FAILURE);
	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	pipes_handler(data->cmd, cmd);
	io_fd_handler(cmd->io_fds);
	close_fd(cmd, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		dprintf(2,"EXEC : %s\n",cmd->command);
		res = exec_builtins(data, cmd);
		if (res != CMD_NOT_FOUND)
		{
			dprintf(2,"SUCCES BUILTIN: %s\n",cmd->command);
			exit_shell(data, res);
		}
		res = exec_with_path(data, cmd);
		if (res != CMD_NOT_FOUND)
		{
			dprintf(2,"SUCCESS CMD NORMAL: %s\n",cmd->command);
			exit_shell(data, res);
		}
	}
	res = launch_command(data, cmd);
	dprintf(2,"EXECUTING END : %s\n",cmd->command);
	exit_shell(data, res);
	return (res);
}

int	executing(t_data *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_infile_outfile(data->cmd->io_fds))
	{
		io_fd_handler(data->cmd->io_fds);
		ret = exec_builtins(data, data->cmd);
		io_fd_restore(data->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_childrens(data));
}
