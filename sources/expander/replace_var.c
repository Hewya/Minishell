/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:07:09 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/25 21:10:17 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*erase_and_replace(t_token **token_node, char *str, char *var_value,
		size_t *index)
{
	char	*newstr;
	int		newstr_size;
	size_t	vl;

	vl = var_length(str + *index);
	newstr_size = (ft_strlen(str) - vl + ft_strlen(var_value));
	newstr = get_new_token_string(str, var_value, newstr_size, *index);
	*index += vl;
	if (token_node && *token_node)
	{
		free_ptr((*token_node)->str);
		(*token_node)->str = newstr;
	}
	return (newstr);
}

int	replace_var(t_token **token_node, char *var_value, size_t *index)
{
	if (var_value == NULL)
	{
		if (erase_and_replace(token_node, (*token_node)->str,
				"", index) == NULL)
			return (1);
	}
	else
	{
		if (erase_and_replace(token_node, (*token_node)->str, var_value,
				index) == NULL)
			return (1);
	}
	free_ptr(var_value);
	return (0);
}

char	*replace_str_heredoc(char *str, char *var_value, size_t index)
{
	char	*tmp;

	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_and_replace(NULL, str, var_value, &index);
		free_ptr(tmp);
	}
	free_ptr(var_value);
	return (str);
}
