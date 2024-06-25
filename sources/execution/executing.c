/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:52:45 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/25 23:47:26 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)
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

	res = FAILURE;
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

	res = FAILURE;
	if (!cmd || !cmd->command)
		exit_minishell(data, EXIT_FAILURE);
	if (!check_infile_outfile(cmd->io_fds))
		exit_minishell(data, EXIT_FAILURE);
	if (pipes_handler(cmd) == -1)
		ft_putendl_fd("error in exec_command pipes", 2); // free and exit en +
	close_pipes(cmd);
	if (io_fd_handler(cmd->io_fds) == -1)
		ft_putendl_fd("error in exec_command io_fd_handler", 2); //free and exit en +
	close_fd(cmd);
	res = call_exec(data, cmd);
	exit_minishell(data, res);
	return (res);
}
// LANCEMENT EXECUTION
int	executing(t_data *data)
{
	int	res;

	res = prep_for_exec(data);
	if (res != CMD_NOT_FOUND)
		return (res);
	if (data == NULL || data->cmd == NULL)
		return (SUCCESS);
	if (check_builtins(data->cmd->command) && (!data->cmd->next)
		&& (!data->cmd->prev))
		res = exec_builtins(data, data->cmd);
	if (res != FAILURE)
		return (res);
	else
	{
		free_data(data , false);
		// return (127);
	}
	create_pipes(data);
	create_childrens(data);
	return (0);
}

/*
int	main(void)
{
	t_data data;
	t_command cmd;
	char *command = "ls";
	char *args[] = {
		"FU=HEU",
		"hello",
		NULL
	};
	char *env[] = {
		"FUCK=YEAH",
		"PWD=ici",
		"PATH=/usr/bin",
		"USER=test_user",
		NULL
	};

	data.env = env;
	data.cmd = &cmd;

	cmd.args = args;
	cmd.prev = NULL;
	cmd.command = command;

	executing(&data);
	return (0);
}*/


/*int	executing(t_data *data)
{
	int command;

	command = FAILURE;
	if (data == NULL || data->cmd == NULL)
		return (SUCCESS);
	else
		create_pipes(data);
	if (data->cmd->prev == NULL && check_builtins(data->cmd->command))
	{
		io_fd_handler(data->cmd->io_fds);
		command = exec_builtins(data);
		io_fd_restore(data->cmd->io_fds);
	}
	if (command != FAILURE)
		return (command);
	create_childrens(data);
	return (wait_childrens(data));
}*/
