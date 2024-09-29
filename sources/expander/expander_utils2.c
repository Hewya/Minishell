/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:51:43 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/29 02:24:54 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_expand_part4(t_token **token, size_t *i, char *rest, char **tokens)
{
	if (ft_strchr(" \t", (*tokens)[ft_strlen(*tokens) - 1]) == NULL)
	{
		concat(&(*token)->str, rest);
		free(rest);
	}
	else
	{
		create_split(token, rest);
		*i = 0;
	}
	ft_free_tab((void **)tokens);
}

static void	_expand_part3(t_token **token, size_t *i, char **tokens, char *rest)
{
	char	**itr;

	itr = tokens;
	if (ft_strchr(" \t", **tokens) == NULL || *i == 0)
	{
		*i = concat(&(*token)->str, *itr);
		++itr;
	}
	while (*itr)
	{
		create_split(token, ft_strdup(*itr));
		*i = ft_strlen(*itr);
		++itr;
	}
	_expand_part4(token, i, rest, tokens);
}

static void	_expand_part2(t_token **token, size_t *i, char *var_name, char *var)
{
	char	**tokens;
	char	*rest;

	tokens = ft_multi_split(var, " \t");
	rest = ft_strdup(&(*token)->str[*i + 1 + ft_strlen(var_name)]);
	(*token)->str[*i] = '\0';
	_expand_part3(token, i, tokens, rest);
	free(var_name);
	free(var);
}

void	expand_part1(t_data *data, t_token **token, size_t *i)
{
	char	*var_name;
	char	*var;

	var_name = identify_var(&(*token)->str[*i]);
	*ft_strchr(var_name, '=') = '\0';
	var = recover_value(*token, &(*token)->str[*i], data);
	if (var == NULL || var[0] == '\0')
	{
		replace_var(token, var, i);
		free(var_name);
		return ;
	}
	_expand_part2(token, i, var_name, var);
}
