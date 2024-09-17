/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:08:48 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/17 19:28:53 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == UNQUOTED)
		{
			if (str[i] == '\'')
				status = SINGLE_QUOTE;
			if (str[i] == '\"')
				status = DOUBLE_QUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SINGLE_QUOTE) || (str[i] == '\"'
				&& status == DOUBLE_QUOTE))
		{
			status = UNQUOTED;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	quotes_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	handle_quotes(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if ((quotes_in_string(tmp->str) == true)
				&& (!tmp->prev || (tmp->prev && tmp->prev->type != HEREDOC)))
			remove_quotes(&tmp);
		tmp = tmp->next;
	}
	return (0);
}
