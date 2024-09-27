/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:01:13 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/27 13:17:45 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_status(t_token *token_node, char *str)
{
	while (1)
	{
		if (*str == '\'' && token_node->status != DOUBLE_QUOTE)
		{
			if (token_node->status == UNQUOTED)
				token_node->status = SINGLE_QUOTE;
			else if (token_node->status == SINGLE_QUOTE)
				token_node->status = UNQUOTED;
			ft_strcpy(str, str + 1);
			if (token_node->prev != NULL && token_node->prev->type == HEREDOC)
				token_node->prev->type = HEREDOC_NO_EXPAND;
			continue ;
		}
		if (*str == '\"' && token_node->status != SINGLE_QUOTE)
		{
			if (token_node->status == UNQUOTED)
				token_node->status = DOUBLE_QUOTE;
			else if (token_node->status == DOUBLE_QUOTE)
				token_node->status = UNQUOTED;
			ft_strcpy(str, str + 1);
			if (token_node->prev != NULL && token_node->prev->type == HEREDOC)
				token_node->prev->type = HEREDOC_NO_EXPAND;
			continue ;
		}
		break ;
	}
}

static bool	is_next_char_valid(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static void	expand(t_data *data, t_token **token, size_t *i)
{
	if ((*token)->str[*i] != '$')
		++(*i);
	else if ((*token)->prev != NULL && ((*token)->prev->type == HEREDOC || (*token)->prev->type == HEREDOC_NO_EXPAND))
		++(*i);
	else if ((*token)->str[*i + 1] == '\'' && (*token)->status == UNQUOTED)
		ft_strcpy(&(*token)->str[*i], &(*token)->str[*i + 1]);
	else if ((*token)->str[*i + 1] == '\"' && (*token)->status == UNQUOTED)
		ft_strcpy(&(*token)->str[*i], &(*token)->str[*i + 1]);
	else if (!is_next_char_valid((*token)->str[*i + 1])
		&& (*token)->str[*i + 1] != '$' && (*token)->str[*i + 1] != '?')
		++(*i);
	else if ((*token)->status != SINGLE_QUOTE)
		replace_var(token, recover_value(*token, &(*token)->str[*i], data), i);
	else
		++(*i);
}

int	var_expander(t_data *data, t_token **token_lst)
{
	t_token	*tmp;
	size_t	i;

	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->type == VAR || tmp->type == WORD)
		{
			tmp->status = UNQUOTED;
			i = 0;
			while (tmp->str[i])
			{
				update_status(tmp, &tmp->str[i]);
				expand(data, &tmp, &i);
			}
		}
		tmp = tmp->next;
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
			&& is_next_char_valid(str[i + 1]))
			str = replace_str_heredoc(str,
					recover_value(NULL, str + i, data), i);
		i++;
	}
	return (str);
}
