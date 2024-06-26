/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:49:09 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/26 20:29:54 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_args(t_command *cmd)
{
	int	i;

	if (!cmd->args)
		ft_printf("\tNo args\n");
	i = 0;
	while (cmd->args[i])
	{
		ft_printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		i++;
	}
}

void	print_cmd_io(t_command *cmd)
{
	if (!cmd->io_fds)
		ft_printf("\tNo io_fds\n");
	if (cmd->io_fds->infile)
	{
		ft_printf("\tInfile: %s\n", cmd->io_fds->infile);
		ft_printf("\t\tfd_in: %d\n", cmd->io_fds->fd_in);
	}
	if (cmd->io_fds->delimiter)
		ft_printf("\tHeredoc delimiter: %s\n", cmd->io_fds->delimiter);
	if (cmd->io_fds->outfile)
	{
		ft_printf("\tOutfile: %s\n", cmd->io_fds->outfile);
		ft_printf("\t\tfd_in: %d\n", cmd->io_fds->fd_out);
	}
}

void	print_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	ft_printf("\n---- COMMAND LIST\n");
	while (cmd)
	{
		ft_printf("--- Command = %s\n", cmd->command);
		print_cmd_args(cmd);
		ft_printf("\tPipe_output = %d\n", cmd->pipe_output);
		print_cmd_io(cmd);
		if (cmd->prev == NULL)
			ft_printf("\tprev = NULL\n");
		else
			ft_printf("\tprev = %s\n", cmd->prev->command);
		if (cmd->next == NULL)
			ft_printf("\tnext = NULL\n");
		else
			ft_printf("\tnext = %s\n", cmd->next->command);
		ft_printf("\n");
		cmd = cmd->next;
	}
	ft_printf("\n");
}

void	print_token_type(t_token *token, char *prefix)
{
	ft_printf("%s", prefix);
	if (token->type == SPACES)
		ft_printf("SPACES\n");
	else if (token->type == WORD)
		ft_printf("WORD\n");
	else if (token->type == VAR)
		ft_printf("VAR\n");
	else if (token->type == PIPE)
		ft_printf("PIPE\n");
	else if (token->type == INPUT)
		ft_printf("INPUT\n");
	else if (token->type == TRUNC)
		ft_printf("TRUNC\n");
	else if (token->type == HEREDOC)
		ft_printf("HEREDOC\n");
	else if (token->type == APPEND)
		ft_printf("APPEND\n");
	else if (token->type == END)
		ft_printf("END\n");
}

void	print_token_status(t_token *token, char *prefix)
{
	ft_printf("%s", prefix);
	if (token->status == UNQUOTED)
		ft_printf("UNQUOTED\n");
	else if (token->status == SINGLE_QUOTE)
		ft_printf("SINGLE_QUOTE\n");
	else if (token->status == DOUBLE_QUOTE)
		ft_printf("DOUBLE_QUOTE\n");
}
void	print_token_var(t_token *token, char *prefix)
{
	ft_printf("%s", prefix);
	if (token->var_exist == true)
		ft_printf("true\n");
	else if (token->var_exist == false)
		ft_printf("false\n");
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = get_first_node(head);
	if (current == NULL)
	{
		ft_printf("Token list is empty.\n");
		return ;
	}
	while (current != NULL)
	{
		ft_printf("Token: %s\n", current->str);
		ft_printf("Backup: %s\n", current->str_backup);
		print_token_type(current, "Types: ");
		print_token_status(current, "Status: ");
		print_token_var(current, "Var Exist: ");
		ft_printf("Quote handle: %d\n", current->join);
		ft_printf("----\n");
		current = current->next;
	}
}

t_token	*get_first_node(t_token *node)
{
	if (node == NULL)
		return (NULL);
	while (node->prev != NULL)
		node = node->prev;
	return (node);
}
