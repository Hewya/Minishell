/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:10:14 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/23 17:17:30 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_cmd(t_command **cmd)
{
	(*cmd)->args = NULL;
	(*cmd)->path = NULL;
	(*cmd)->command = NULL;
	(*cmd)->pipe_fd = 0;
	(*cmd)->pipe_output = false;
	(*cmd)->next = NULL;
	(*cmd)->prev = NULL;
	(*cmd)->io_fds = NULL;
}

t_command	*lst_new_cmd(bool value)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_command));
	new->pipe_output = value;
	initialize_cmd(&new);
	return (new);
}

void	lst_add_back_cmd(t_command **alst, t_command *new)
{
	t_command	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new;
		return ;
	}
	if (alst && *alst && new)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new;
		new->prev = start;
	}
}

t_command	*lst_last_cmd(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
