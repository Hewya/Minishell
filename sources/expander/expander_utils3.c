/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 01:01:55 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/29 01:28:18 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_split(t_token **base, char *content)
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

size_t	concat(char **dst_ptr, char *str)
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
