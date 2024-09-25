/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:01:13 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/25 22:56:46 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static bool	is_next_char_valid(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static void	expand(t_data *data, t_token **token, size_t *i, bool *flag)
{
	if ((*token)->str[*i] != '$')
		++(*i);
	else if ((*token)->str[*i + 1] == '\'')
	{
		ft_strcpy(&(*token)->str[*i], &(*token)->str[*i + 2]);
		while ((*token)->str[*i] && (*token)->str[*i] != '\'')
			++*i;
		ft_strcpy(&(*token)->str[*i], &(*token)->str[*i + 1]);
	}
	else if ((*token)->str[*i + 1] == '\"')
	{
		if (!*flag)
			ft_strcpy(&(*token)->str[*i], &(*token)->str[*i + 1]);
		*i += *flag == true;
		*flag = !*flag;
	}
	else if ((*token)->status != SINGLE_QUOTE)
		replace_var(token,
			recover_value(*token, (*token)->str + *i, data), i);
	else
		++(*i);
}

int	var_expander(t_data *data, t_token **token_lst)
{
	t_token	*tmp;
	size_t	i;
	bool	flag;

	flag = false;
	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			i = 0;
			while (tmp->str[i])
			{
				update_status(&tmp, tmp->str[i]);
				expand(data, &tmp, &i, &flag);
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
