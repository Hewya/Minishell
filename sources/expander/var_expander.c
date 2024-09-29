/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:01:13 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/29 02:21:44 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_first_char_valid(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static const char	*search(const char *to_search, const char *to_find)
{
	while (*to_search)
		if (strchr(to_find, *to_search++))
			return (to_search - 1);
	return (NULL);
}

static void	expand(t_data *data, t_token **token, size_t *i)
{
	if ((*token)->prev != NULL
		&& ((*token)->prev->type == HEREDOC
			|| (*token)->prev->type == HEREDOC_NO_EXPAND))
		++(*i);
	else if (ft_strchr("\'\"", (*token)->str[*i + 1])
		&& (*token)->status == UNQUOTED)
		ft_strcpy(&(*token)->str[*i], &(*token)->str[*i + 1]);
	else if (!is_first_char_valid((*token)->str[*i + 1])
		&& ft_strchr("$?", (*token)->str[*i + 1]) == NULL)
		++(*i);
	else if ((*token)->status == DOUBLE_QUOTE)
		replace_var(token, recover_value(*token, &(*token)->str[*i], data), i);
	else if ((*token)->status == UNQUOTED)
		expand_part1(data, token, i);
	else
		++(*i);
}

int	var_expander(t_data *data, t_token **token_lst)
{
	const char	*interest;
	t_token		*tmp;
	size_t		i;

	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->type == VAR || tmp->type == WORD)
		{
			tmp->status = UNQUOTED;
			interest = search(tmp->str, "$\'\"");
			while (interest)
			{
				i = interest - tmp->str;
				update_status(tmp, &tmp->str[i]);
				if (tmp->str[i] == '$' && tmp->str[i + 1] != '\0')
					expand(data, &tmp, &i);
				else
					++i;
				interest = search(&tmp->str[i], "$\'\"");
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*var_expander_heredoc(t_data *data, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_first_char_valid(str[i + 1]))
			str = replace_str_heredoc(str,
					recover_value(NULL, str + i, data), i);
		++i;
	}
	return (str);
}
