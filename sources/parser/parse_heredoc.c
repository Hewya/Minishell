/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antoine Massias <massias.antoine.pro@gm    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:24:29 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/26 01:04:03 by Antoine Mas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DEFAULT_RESULT_SIZE 32

bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, io, tmp_fd);
	close(tmp_fd);
	return (ret);
}

static char	*get_heredoc_name(void)
{
	static int	i = 0;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

// `*result` musn't be NULL
static char	*append_char(char **result, size_t *result_capacity, char c)
{
	size_t	length;
	char	*tmp;

	length = strlen(*result);
	if (length + 1 == *result_capacity)
	{
		tmp = malloc(*result_capacity * 2);
		if (tmp == NULL)
			return (NULL);
		memcpy(tmp, *result, length);
		free(*result);
		*result = tmp;
	}
	(*result)[length] = c;
	(*result)[length + 1] = '\0';
	return (*result);
}

static char	*get_delim(char *delim)
{
	char	*result;
	size_t	result_capacity;
	char	quote;

	result_capacity = DEFAULT_RESULT_SIZE;
	result = calloc(DEFAULT_RESULT_SIZE, 1);
	while (result != NULL && *delim)
	{
		if (*delim == '\'' || *delim == '\"')
		{
			quote = *delim++;
			while (*delim && *delim != quote)
				if (append_char(&result, &result_capacity, *delim++) == NULL)
					return (free(result), NULL);
			if (*delim++ != quote)
				return (free(result), NULL);
		}
		else if (append_char(&result, &result_capacity, *delim++) == NULL)
			return (free(result), NULL);
	}
	return (result);
}

void	parse_heredoc(t_data *data, t_command **last_cmd, t_token **token_lst)
{
	t_token		*tmp;
	t_command	*cmd;
	t_io_fds	*io;

	tmp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	io = cmd->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = get_heredoc_name();
	io->delimiter = get_delim(tmp->next->str);
	if (io->delimiter == NULL)
		exit_shell(data, 3);
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*token_lst = tmp;
}
