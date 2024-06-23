/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childrens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:03:11 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/23 17:55:27 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		wait_childrens(t_data *data)
{
	close_fd(data);
    return (0);
}

int		create_childrens(t_data *data)
{
    t_command *command;

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
            exec_command(data);
        command = command->next;
    }
    return (0);
}
