/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:22:05 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/22 12:53:16 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp && (tmp->type == WORD || tmp->type == VAR))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	create_args_default_mode(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*tmp;

	i = 0;
	tmp = *token_node;
	nb_args = count_arguments(tmp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	tmp = *token_node;
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		last_cmd->args[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = tmp;
	return (SUCCESS);
}
/**
 * @brief Creates a new table of strings, copies the default environment
 * variables from the original table, and returns the new table. The function
 * allocates memory for the new table and each string, and then duplicates
 * the default environment variables from the original table to the new one.
 */
static char	**copy_default_in_new_tab(int len, char **new_tab,
		t_command *last_cmd, t_token **tk_node)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *tk_node;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == VAR)
	{
		new_tab[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	add_args_default_mode(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*tmp;

	i = 0;
	tmp = *token_node;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		i++;
		tmp = tmp->next;
	}
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_default_in_new_tab(len, new_tab, last_cmd, token_node);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	*token_node = tmp;
	return (SUCCESS);
}

int	fill_args(t_token **token_node, t_command *last_cmd)
{
	if (!ft_strcmp(last_cmd->command, "echo"))
	{
		if (!(last_cmd->args))
			return (create_args_echo_mode(token_node, last_cmd));
		else
			return (add_args_echo_mode(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			return (create_args_default_mode(token_node, last_cmd));
		else
			return (add_args_default_mode(token_node, last_cmd));
	}
	return (SUCCESS);
}
