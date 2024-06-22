/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:59:34 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/22 12:52:32 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a string contains a space character.
 */
static bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Splits a command string into individual tokens, handling variables,
 * commands, and arguments. It allocates memory for the tokens, initializes the
 * token structures, and populates the token lists.The function takes a
 * command string as input, splits it into tokens using spaces as delimiters,
 * and then processes each token to determine its type (variable, command, or
 * argument). It handles variables by extracting their values from the
 * environment, and commands by setting up their argument lists. The function
 * returns a pointer to the first token in the list, which can be used to
 * traverse the token list.
 */
static void	split_var_cmd_token(t_command *last_cmd, char *cmd_str)
{
	t_token	*new_token;
	t_token	*tmp;
	char	**strs;
	int		i;

	new_token = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_token = lst_new_token(ft_strdup(strs[1]), NULL, WORD, UNQUOTED);
	tmp = new_token;
	i = 1;
	while (strs[++i])
		lst_add_back_token(&new_token, lst_new_token(ft_strdup(strs[i]), NULL,
				WORD, UNQUOTED));
	lst_add_back_token(&new_token, lst_new_token(NULL, NULL, END, UNQUOTED));
	fill_args(&new_token, last_cmd);
	lst_clear_token(&tmp, &free_ptr);
	free_str_tab(strs);
}

void	parse_word(t_command **cmds, t_token **token_lst)
{
	t_token		*tmp;
	t_command	*last_cmd;

	tmp = *token_lst;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		last_cmd = lst_last_cmd(*cmds);
		if (tmp->prev == NULL || (tmp->prev && tmp->prev->type == HEREDOC)
			|| last_cmd->command == NULL)
		{
			if (tmp->type == VAR && contains_space(tmp->str))
				split_var_cmd_token(last_cmd, tmp->str);
			else
				last_cmd->command = ft_strdup(tmp->str);
			tmp = tmp->next;
		}
		else
			fill_args(&tmp, last_cmd);
	}
	*token_lst = tmp;
}
