/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:52:45 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/23 18:37:46 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	exit_minishell(t_data *data)
{
//close_fds
//io_fd_restore
//close_pipes
}
*/
int		g_last_exit_code;

int	exec_builtins(t_data *data)
{
	int	res;

	res = FAILURE;
	if (ft_strncmp(data->cmd->command, "cd", 2) == 0)
		res = cd_builtin(data);
	else if (ft_strncmp(data->cmd->command, "echo", 4) == 0)
		res = echo_builtin(data);
	else if (ft_strncmp(data->cmd->command, "env", 3) == 0)
		res = env_builtin(data);
	else if (ft_strncmp(data->cmd->command, "export", 6) == 0)
		res = export_builtin(data);
	else if (ft_strncmp(data->cmd->command, "pwd", 3) == 0)
		res = pwd_builtin();
	else if (ft_strncmp(data->cmd->command, "unset", 5) == 0)
		res = unset_builtin(data);
	else if (ft_strncmp(data->cmd->command, "exit", 4) == 0)
		res = exit_builtin();
	return (res);
}

int	exec_command(t_data *data)
{
	int	res;

	res = FAILURE;
	if (pipes_handler(data) == -1)
		ft_putendl_fd("error in exec_command pipes", 2); // free and exit
	close_pipes(data);
	if (io_fd_handler(data->cmd->io_fds) == -1)
		ft_putendl_fd("error in exec_command io_fd_handler", 2);
			// free and exit
	close_fd(data);
	if (check_builtins(data->cmd->command))
		res = exec_builtins(data);
	else
		call_exec(data);
	// exit_minishell
	return (res);
}

/*int	executing(t_data *data)
{
	int	res;

	res = FAILURE;
	if (data == NULL || data->cmd == NULL)
		return (SUCCESS);
	if (check_builtins(data->cmd->command) && (!data->cmd->next)
		&& (!data->cmd->prev))
		res = exec_builtins(data);
	if (res != FAILURE)
		return (res);
	create_pipes(data);
	create_childrens(data);
	return (0);
}*/

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


int	executing(t_data *data)
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
}
