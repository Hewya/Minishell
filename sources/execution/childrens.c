/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childrens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:03:11 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/25 23:52:41 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
explication :

"If there are multiple commands in a pipeline:
		"The exit status of a pipeline is the exit status of the last
		command in the pipeline"

"The return status of a simple command is :
	its exit status as provided by the POSIX 1003.1 waitpid function,
		or 128+n if the command was terminated by signal n."

The while loop continues until waitpid returns -1 and errno is ECHILD,
	indicating that there are no more child processes.

----

WIFSIGNALED(save_status): Checks if the child process was terminated by a signal.

If true, status is set to 128 + the signal number (WTERMSIG(save_status)).
WIFEXITED(save_status): Checks if the child process terminated normally.

If true,
	status is set to the exit status of the child (WEXITSTATUS(save_status)).
If neither condition is true, status is set directly to save_status.

*/

int	wait_childrens(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	wpid = 0;
	status = 0;
	save_status = 0;
	close_fd(data->cmd);
	close_pipes(data->cmd);
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				continue ;
		}
		if (wpid == data->pid)
			save_status = status;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status); // signal effect
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

int	create_childrens(t_data *data)
{
	t_command	*command;

	command = data->cmd;
	while (command && data->pid != 0)
	{
		data->pid = fork();
		if (data->pid < 0)
		{
			ft_putendl_fd("error with childrens", 2);
			return (FAILURE);
		}
		else if (data->pid == 0)
			exec_command(data, command);
		command = command->next;
	}
	return (0);
}
