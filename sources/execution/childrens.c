/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childrens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:03:11 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/29 17:39:11 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childrens(t_data *data)
{
	t_command	*command;
	int			status;

	close_fd(data->cmd, false);
	status = 0;
	command = data->cmd;
	while (command != NULL)
	{
		waitpid(command->pid, &status, 0);
		command = command->next;
	}
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	create_childrens(t_data *data)
{
	t_command	*command;

	command = data->cmd;
	while (command && data->pid != 0)
	{
		command->pid = fork();
		if (command->pid == -1)
		{
			ft_putendl_fd("error with childrens", 2);
			exit_shell(data, EXIT_FAILURE);
		}
		else if (command->pid == 0)
			exec_command(data, command);
		command = command->next;
	}
	return (wait_childrens(data));
}
