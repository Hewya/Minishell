/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:19:20 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/23 17:17:05 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->str[*i] == '\'')
		(*token_node)->status = SINGLE_QUOTE;
	if ((*token_node)->str[*i] == '\"')
		(*token_node)->status = DOUBLE_QUOTE;
	(*i)++;
}

static bool	if_quotes_and_unquoted(t_token **token_node, int i)
{
	if (((*token_node)->str[i] == '\'' || (*token_node)->str[i] == '\"')
		&& (*token_node)->status == UNQUOTED)
		return (true);
	else
		return (false);
}

static bool	change_back_to_unquoted(t_token **token_node, int *i)
{
	if (((*token_node)->str[*i] == '\''
			&& (*token_node)->status == SINGLE_QUOTE)
		|| ((*token_node)->str[*i] == '\"'
			&& (*token_node)->status == DOUBLE_QUOTE))
	{
		(*token_node)->status = UNQUOTED;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->str, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->str[i])
	{
		if (if_quotes_and_unquoted(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_unquoted(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->str[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_line;
	(*token_node)->join = true;
	return (0);
}
