/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:49:09 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/22 12:57:12 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_args(t_command *cmd)
{
	int	i;

	if (!cmd->args)
		printf("\tNo args\n");
	i = 0;
	while (cmd->args[i])
	{
		printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		i++;
	}
}

void	print_cmd_io(t_command *cmd)
{
	if (!cmd->io_fds)
		printf("\tNo io_fds\n");
	if (cmd->io_fds->infile)
	{
		printf("\tInfile: %s\n", cmd->io_fds->infile);
		printf("\t\tfd_in: %d\n", cmd->io_fds->fd_in);
	}
	if (cmd->io_fds->delimiter)
		printf("\tHeredoc delimiter: %s\n", cmd->io_fds->delimiter);
	if (cmd->io_fds->outfile)
	{
		printf("\tOutfile: %s\n", cmd->io_fds->outfile);
		printf("\t\tfd_in: %d\n", cmd->io_fds->fd_out);
	}
}

void	print_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	printf("\n---- COMMAND LIST\n");
	while (cmd)
	{
		printf("--- Command = %s\n", cmd->command);
		print_cmd_args(cmd);
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		print_cmd_io(cmd);
		if (cmd->prev == NULL)
			printf("\tprev = NULL\n");
		else
			printf("\tprev = %s\n", cmd->prev->command);
		if (cmd->next == NULL)
			printf("\tnext = NULL\n");
		else
			printf("\tnext = %s\n", cmd->next->command);
		printf("\n");
		cmd = cmd->next;
	}
	printf("\n");
}

void	print_token_type(t_token *token, char *prefix)
{
	printf("%s", prefix);
	if (token->type == SPACES)
		printf("SPACES\n");
	else if (token->type == WORD)
		printf("WORD\n");
	else if (token->type == VAR)
		printf("VAR\n");
	else if (token->type == PIPE)
		printf("PIPE\n");
	else if (token->type == INPUT)
		printf("INPUT\n");
	else if (token->type == TRUNC)
		printf("TRUNC\n");
	else if (token->type == HEREDOC)
		printf("HEREDOC\n");
	else if (token->type == APPEND)
		printf("APPEND\n");
	else if (token->type == END)
		printf("END\n");
}

void	print_token_status(t_token *token, char *prefix)
{
	printf("%s", prefix);
	if (token->status == UNQUOTED)
		printf("UNQUOTED\n");
	else if (token->status == SINGLE_QUOTE)
		printf("SINGLE_QUOTE\n");
	else if (token->status == DOUBLE_QUOTE)
		printf("DOUBLE_QUOTE\n");
}
void	print_token_var(t_token *token, char *prefix)
{
	printf("%s", prefix);
	if (token->var_exist == true)
		printf("true\n");
	else if (token->var_exist == false)
		printf("false\n");
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = get_first_node(head);
	if (current == NULL)
	{
		printf("Token list is empty.\n");
		return ;
	}
	while (current != NULL)
	{
		printf("Token: %s\n", current->str);
		printf("Backup: %s\n", current->str_backup);
		print_token_type(current, "Types: ");
		print_token_status(current, "Status: ");
		print_token_var(current, "Var Exist: ");
		printf("Quote handle: %d\n", current->join);
		printf("----\n");
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
