/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:56:19 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/20 20:54:26 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief _link_extremities function is used to link the insert node between
			two existing nodes in a doubly linked list.
*/
void	_link_extremities(t_token *to_del, t_token *tmp, t_token *insert)
{
	while (tmp != to_del)
		tmp = tmp->next;
	insert->prev = tmp->prev;
	tmp->prev->next = insert;
	while (insert->next)
		insert = insert->next;
	tmp->next->prev = insert;
	insert->next = tmp->next;
}
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp == NULL)
		*head = insert;
	else if (tmp == to_del)
	{
		*head = insert;
		insert->next = tmp->next;
		if (tmp->next != NULL)
			tmp->next->prev = insert;
	}
	else
		_link_extremities(to_del, tmp, insert);
	free_ptr(to_del->str);
	free(to_del);
	return (insert);
}
