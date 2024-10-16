/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:45:40 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/24 18:21:02 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_separator(t_token **token_lst, char *str, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, UNQUOTED));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, UNQUOTED));
	}
	return (0);
}

int	save_word(t_token **token_lst, char *str, int index, int start)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
		word[i++] = str[start++];
	word[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(word, ft_strdup(word), WORD,
			UNQUOTED));
	return (0);
}

int	is_separator(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}

int	set_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == UNQUOTED)
		status = SINGLE_QUOTE;
	else if (str[i] == '\"' && status == UNQUOTED)
		status = DOUBLE_QUOTE;
	else if (str[i] == '\'' && status == SINGLE_QUOTE)
		status = UNQUOTED;
	else if (str[i] == '\"' && status == DOUBLE_QUOTE)
		status = UNQUOTED;
	return (status);
}

int	save_word_or_sep(int *i, char *str, int start, t_data *data)
{
	int	type;

	type = is_separator(str, (*i));
	if (type)
	{
		if ((*i) != 0 && is_separator(str, (*i) - 1) == 0)
			save_word(&data->token, str, (*i), start);
		if (type == APPEND || type == HEREDOC || type == PIPE || type == TRUNC
			|| type == INPUT || type == END)
		{
			save_separator(&data->token, str, (*i), type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}
