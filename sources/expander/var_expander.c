/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:01:13 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/24 15:41:39 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  Updates the status of a token node based on the current character,
 * switching between unquoted, single-quoted, and double-quoted states.
 */
static void	update_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == UNQUOTED)
		(*token_node)->status = SINGLE_QUOTE;
	else if (c == '\"' && (*token_node)->status == UNQUOTED)
		(*token_node)->status = DOUBLE_QUOTE;
	else if (c == '\'' && (*token_node)->status == SINGLE_QUOTE)
		(*token_node)->status = UNQUOTED;
	else if (c == '\"' && (*token_node)->status == DOUBLE_QUOTE)
		(*token_node)->status = UNQUOTED;
}

/**
 * @brief Checks if the next character in a string is a separator
 * (e.g., space, '$', '=')
 */
static bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

/**
 * @brief  Checks if a variable is enclosed within single or double quotes
 * in a given string.
 */
static bool	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

int	var_expander(t_data *data, t_token **token_lst)
{
	t_token	*temp;
	int		i;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR)
		{
			i = 0;
			while (temp->str[i])
			{
				update_status(&temp, temp->str[i]);
				if (temp->str[i] == '$' && is_next_char_a_sep(temp->str[i + 1])
					== false && var_between_quotes(temp->str, i) == false
					&& (temp->status == UNQUOTED
						|| temp->status == DOUBLE_QUOTE))
					replace_var(&temp, recover_value(temp, temp->str + i, data),
						i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

char	*var_expander_heredoc(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_next_char_a_sep(str[i + 1]) == false
			&& var_between_quotes(str, i) == false)
			str = replace_str_heredoc(str,
					recover_value(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
