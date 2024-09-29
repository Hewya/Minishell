/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:05:18 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/29 00:34:39 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_single_quote(char *str, t_token *token_node)
{
	if (token_node->status == UNQUOTED)
		token_node->status = SINGLE_QUOTE;
	else if (token_node->status == SINGLE_QUOTE)
		token_node->status = UNQUOTED;
	ft_strcpy(str, str + 1);
	if (token_node->prev != NULL && token_node->prev->type == HEREDOC)
		token_node->prev->type = HEREDOC_NO_EXPAND;
}

static void	is_double_quote(char *str, t_token *token_node)
{
	if (token_node->status == UNQUOTED)
		token_node->status = DOUBLE_QUOTE;
	else if (token_node->status == DOUBLE_QUOTE)
		token_node->status = UNQUOTED;
	ft_strcpy(str, str + 1);
	if (token_node->prev != NULL && token_node->prev->type == HEREDOC)
		token_node->prev->type = HEREDOC_NO_EXPAND;
}

void	update_status(t_token *token_node, char *str)
{
	while (1)
	{
		if (*str == '\'' && token_node->status != DOUBLE_QUOTE)
		{
			is_single_quote(str, token_node);
			continue ;
		}
		if (*str == '\"' && token_node->status != SINGLE_QUOTE)
		{
			is_double_quote(str, token_node);
			continue ;
		}
		break ;
	}
}

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

char	*get_new_token_string(char *oldstr, char *var_value, int newstr_size,
		int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (newstr_size + 1));
	if (!new_str)
		return (NULL);
	while (oldstr[i])
	{
		if (oldstr[i] == '$' && i == index)
		{
			copy_var_value(new_str, var_value, &j);
			i = i + var_length(1 + oldstr + index) + 1;
			if (oldstr[i] == '\0')
				break ;
		}
		new_str[j++] = oldstr[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
