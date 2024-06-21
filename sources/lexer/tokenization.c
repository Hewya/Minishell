/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:45:35 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/21 18:44:17 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization(t_data *data, char *str)
{
	int	i;
	int	start;
	int	end;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = UNQUOTED;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == UNQUOTED)
			start = save_word_or_sep(&i, str, start, data);
	}
	if (status != UNQUOTED)
	{
		if (status == DOUBLE_QUOTE)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SINGLE_QUOTE)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
