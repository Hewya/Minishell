/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassias <amassias@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:01:13 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/28 18:45:10 by amassias         ###   ########.fr       */
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

static bool	is_first_char_valid(char c)
{
	return (ft_isalpha(c) || c == '_');
}

// Creates a new token who's content has been set to `content`
// and places it right after the current token
// then sets the current token to the new one.
//
// Visual representation (The '*' represents the currently selected token (`*base`)):
// ...<->[*a]<->[b]<->...
// will become:
// ...<->[a]<->[*new token]<->[b]<->...
static void	_create_split(t_token **base, char *content)
{
	t_token	*new_token;

	new_token = lst_new_token(content, NULL, (*base)->type, UNQUOTED);
	new_token->next = (*base)->next;
	if (new_token->next)
		new_token->next->prev = new_token;
	new_token->prev = *base;
	(*base)->next = new_token;
	*base = new_token;
}

// Appends `str` to `*dst_ptr` and returns the length of the result.
static size_t	_concat(char **dst_ptr, char *str)
{
	size_t	new_len;
	char	*result;

	new_len = ft_strlen(*dst_ptr) + ft_strlen(str);
	result = malloc(new_len + 1);
	result[0] = '\0';
	ft_strcat(result, *dst_ptr);
	ft_strcat(result, str);
	free(*dst_ptr);
	*dst_ptr = result;
	return (new_len);
}

// TODO: Check for bad allocs (malloc(...) == NULL)
static void	_expand(t_data *data, t_token **token, size_t *i)
{
	char	*var_name;
	char	*var;
	char	*rest;
	char	**tokens;
	char	**itr;

	// Extracting variable name
	var_name = identify_var(&(*token)->str[*i]);
	// Removing the trailing '='
	*ft_strchr(var_name, '=') = '\0';
	// Query variable content
	var = recover_value(*token, &(*token)->str[*i], data);
	// If the variable is empty, use the basic variable expander
	if (var == NULL || var[0] == '\0')
	{
		replace_var(token, var, i);
		free(var_name);
		return ;
	}
	// Splitting variable content into 'bits'
	tokens = ft_multi_split(var, " \t");
	// Making a copy of what comes after the variable
	rest = ft_strdup(&(*token)->str[*i + 1 + ft_strlen(var_name)]);
	// Ending the current tokens's content right where the '$' is
	(*token)->str[*i] = '\0';
	itr = tokens;
	// If the variable's content does not start with a 'space',
	// append the first variable 'bit' to the current token's content
	// and skip to the next variable 'bit'
	if (ft_strchr(" \t", *var) == NULL || *i == 0)
	{
		*i = _concat(&(*token)->str, *itr);
		++itr;
	}
	// For each remaining variable bit
	while (*itr)
	{
		// Create a new token who's value will be the current variable 'bit'
		_create_split(token, ft_strdup(*itr));
		*i = ft_strlen(*itr);
		++itr;
	}
	// If the variable's content does not end with a 'space',
	// append the last variable 'bit' to the current token's content
	if (ft_strchr(" \t", var[ft_strlen(var) - 1]) == NULL)
	{
		_concat(&(*token)->str, rest);
		free(rest);
	}
	// Create a new token who's value will be the last variable 'bit'
	else
	{
		_create_split(token, rest);
		*i = 0;
	}
	// Cleanup
	free(var_name);
	free(var);
	ft_free_tab((void **)tokens);
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
		_expand(data, token, i);
	else
		++(*i);
}

// Searches for the first occurence of any char of `to_find` into `to_search`.
// If none were found, returns NULL.
static
const char	*_search(const char *to_search, const char *to_find)
{
	while (*to_search)
		if (strchr(to_find, *to_search++))
			return (to_search - 1);
	return (NULL);
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
			interest = _search(tmp->str, "$\'\"");
			while (interest)
			{
				i = interest - tmp->str;
				update_status(tmp, &tmp->str[i]);
				if (tmp->str[i] == '$' && tmp->str[i + 1] != '\0')
					expand(data, &tmp, &i);
				else
					++i;
				interest = _search(&tmp->str[i], "$\'\"");
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
