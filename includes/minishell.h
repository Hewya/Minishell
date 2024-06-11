/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:41:26 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/11 17:56:05 by gabarnou         ###   ########.fr       */
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

//token_lst_utils.c
t_token	*lst_new_node(char *str, char *str_backup, int type, int status);
void	lst_add_back(t_token **alst, t_token *new_node);
void	lst_del_one_token(t_token *lst, void (*del)(void *));
void	lst_clear(t_token **lst, void (*del)(void *));

//token_lst_utils_2.c


/* ------------------------------ UTILS --------------------------------------*/

//clean_up.c
void	free_ptr(void *ptr);

#endif
