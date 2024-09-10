/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childrens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:03:11 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/28 14:45:52 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childrens(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fd(data->cmd, false);
	wpid = 0;
	status = 0;
	save_status = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue;
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
		if (data->pid == -1)
		{
			ft_putendl_fd("error with childrens", 2);
			return (EXIT_FAILURE);
		}
		else if (data->pid == 0)
		{
			exec_command(data, command);
		}
		command = command->next;
	}
	return (wait_childrens(data));
}
