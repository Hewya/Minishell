/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:41:26 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/12 01:07:30 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */

# include <unistd.h>			// fork, pipe, exec, read, write, close, etc.
# include <stdio.h>				// printf, scanf, perror, etc.
# include <stdlib.h>			// malloc, free, exit, etc.
# include <fcntl.h>				// open, creat, fcntl, etc.
# include <stdbool.h>			// boolean
# include <errno.h>				// errno, strerror, etc.
# include <sys/stat.h>			// ?????????
# include <sys/types.h>			// pid_t, uid_t, gid_t, etc.
# include <sys/wait.h>			// wait, waitpid, waitid, etc.
# include <signal.h>			// signal, kill, sigaction, etc.
# include <readline/readline.h>	// readline, add_history, etc.
# include <readline/history.h> 	// add_history, history_list, etc.

# include "includes/libft/libft.h"

/* MACROS */

# define SUCCESS 0
# define FAILURE 1

/* STRUCTURES */

typedef	struct s_token
{
	char			*str;
	char			*str_backup;
	int				type;
	int				status;
	bool			var_exist;
	bool			join;
	struct s_token *prev;
	struct s_token *next;
}				t_token;

typedef	struct s_data
{
	t_token		*token;
	char		*user_input;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	pid_t		pid;
	t_command	*cmd;
}				t_data;

typedef	struct s_command
{
	char				*command;
	char				**args;
	char				*path;
	bool				pipe_output;
	int					*pipe_fd;
	struct s_command	*prev;
	struct s_command	 *next;
	t_io_fds			*io_fds;
}				t_command;

typedef	struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}				t_io_fds;


/* ENUMERATIONS */

enum e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum e_quoting_status
{
	UNQUOTED, // PREFERES TU "DEFAULT" ?
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};

/* ************************************************************************** */
/*  							FUNCTIONS									  */
/* ************************************************************************** */


/* ------------------------------ LEXER --------------------------------------*/

// tokenization.c

/// @brief tokenization : ???
int	tokenization(t_data *data, char *str);

// tokenization_utils.c

/// @brief Define if it is a separator and add it at the end of the list.
int	save_separator(t_token **token_lst, char *str, int index, int type);
/// @brief Define if it is a word and add it at the end of the list.
int	save_word(t_token **token_lst, char *str, int index, int start);
/// @brief Define the type of separator.
int	is_separator(char *str, int i);
/// @brief Define the quotes status.
int	set_status(int status, char *str, int i);
/// @brief Splits input string into words or separators, saving them as tokens in linked list.
int	save_word_or_sep(int *i, char *str, int start, t_data *data);


// token_lst_utils.c

/// @brief creat a new node
t_token	*lst_new_node_token(char *str, char *str_backup, int type, int status);
/// @brief add a new node at the end of the list
void	lst_add_back_token(t_token **alst, t_token *new_node);
/// @brief free one node of the list
void	lst_del_one_token(t_token *lst, void (*del)(void *));
/// @brief free the entire list
void	lst_clear_token(t_token **lst, void (*del)(void *));

// token_lst_utils_2.c

/** @brief _link_extremities function is used to link the insert node between
			two existing nodes in a doubly linked list.*/
void	_link_extremities(t_token *to_del, t_token *temp, t_token *insert);
/** @brief The insert_lst_between function is used to insert a new node (insert)
 *			between two existing nodes in a doubly linked list.*/
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);


/* ------------------------------ UTILS --------------------------------------*/

//clean_up.c

/// @brief  free a pointer
void	free_ptr(void *ptr);

// errors.c

/// @brief Joins two strings and freeing the previous one.
char	*join_strs(char *str, char *add);
/// @brief Prints an error message unrelated to a specific command.
///			 Used in parsing to handle syntax errors
void	errmsg(char *errmsg, char *detail, int quotes);

#endif
