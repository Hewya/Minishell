/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:30:41 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/11 23:44:58 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

char	*join_strs(char *str, char *add)
{
	char	*temp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	temp = str;
	str = ft_strjoin(str, add);
	free_ptr(temp);
	return (str);
}

void	errmsg(char *errmsg, char *detail, int quotes)
{
	char *msg;

	msg = ft_strdup("minishell: ");
	msg = join_strs(msg, errmsg);
	if (quotes)
		msg = join_strs(msg, " `");
	else
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, detail);
	if (quotes)
		msg = join_strs(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}
