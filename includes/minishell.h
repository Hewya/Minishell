/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:41:26 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/21 13:56:51 by gabarnou         ###   ########.fr       */
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
# include <readline/history.h>	// add_history, history_list, etc.

# include ".././libft/libft.h"

/* GLOBAL VARIABLE */
extern int	g_last_exit_code;

/* MACROS */
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define SUCCESS 0
# define FAILURE 1

# define PROMPT "Minishell ->	"

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
}			t_io_fds;

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
}			t_command;


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
	UNQUOTED,
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
/**
 * @brief Splits input string into words or separators, saving them as tokens
 * in linked list.
*/
int	save_word_or_sep(int *i, char *str, int start, t_data *data);


// token_lst_utils.c

/// @brief create a new node
t_token	*lst_new_token(char *str, char *str_backup, int type, int status);
/// @brief add a new node at the end of the list
void	lst_add_back_token(t_token **alst, t_token *new_node);
/// @brief free one node of the list
void	lst_del_one_token(t_token *lst, void (*del)(void *));
/// @brief free the entire list
void	lst_clear_token(t_token **lst, void (*del)(void *));

// token_lst_utils_2.c

/** @brief The insert_lst_between function is used to insert a new node (insert)
 *			between two existing nodes in a doubly linked list.*/
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);

// parse_user_input.c

bool	parse_user_input(t_data *data);

// lexer_grammar.c

int	check_consecutives(t_token **token_lst);

//check_if_var.c

void	_variable_check(t_token **token_node);
int	check_if_var(t_token **token_lst);


/* ----------------------------- EXPANDER ------------------------------------*/

// var_expander.c

/// @brief
int	var_expander(t_data *data, t_token **token_lst);


// var_expander_utils.c

/***
 * @brief Copies the value of an environment variable into a newly allocated
 * string, returning the copied value or NULL on failure.
*/
void	copy_var_value(char *new_str, char *var_value, int *j);
/***
 * @brief Allocates memory for a new token string, initializes it, and
 * returns the pointer to the new token string.
*/
char	*get_new_token_string(char *oldstr, char *var_value, int newstr_size,
			int index);


// replace_var.c

/**
 * @brief Replaces a variable in a token string with its value, erasing
 * the variable notation if no value is provided.
*/
int	replace_var(t_token **token_node, char *var_value, int index);


// identify_var.c

/**
 * @brief Checks if a character is a valid variable name character
 * (alphanumeric or underscore).
*/
bool is_var_friendly(char c);
/**
 * @brief Returns the length of a variable name (excluding the '$' symbol)
 * in a given string.
*/
int	var_length(char *str);
/**
 * @brief Checks if a token is a variable (starts with '$').
*/
char	*identify_var(char *str);


// recover_value.c

/**
 * @brief Retrieves the value of a variable from the environment, handling cases
 * where the variable is not set or has a special value (e.g., $?). It returns
 * a dynamically allocated string containing the variable's value.
*/
char	*recover_value(t_token *token, char *str, t_data *data);


// quotes_handler.c

/**
 * @brief Counts the length of a string until a specific character is
 * encountered, used for handling quoted strings.
*/
int	count_len(char *str, int count, int i);
/**
 * @brief  Checks if a string contains quotes (single or double) and returns
 * true if quotes are found, false otherwise.
*/
bool	quotes_in_string(char *str);
/**
 * @brief  Handles quoted strings by updating the token node's status and
 * string accordingly, taking into account single and double quotes.
*/
int	handle_quotes(t_data *data);


// quotes_remover.c

/**
 * @brief Removes quotes (single or double) from a token string, updating
 * the token node's string and status.
*/
int	remove_quotes(t_token **token_node);


/* ----------------------------- PARSER --------------------------------------*/

// create_command.c

/**
 * @brief Creates a new command structure, allocating memory for the command
 * and its arguments, and initializes the command type and argument list.
*/
void	create_command(t_data *data, t_token *token);


// cmd_lst_utils.c

/**
 * @brief Returns the last command in a linked list of commands.
*/
t_command	*lst_last_cmd(t_command *cmd);
/**
 * @brief Adds a new command to the end of a linked list of commands.
*/
void	lst_add_back_cmd(t_command **alst, t_command *new);
/**
 * @brief Creates a new command node, allocating memory and initializing its
 * fields, and returns a pointer to the new node.
*/
t_command	*lst_new_cmd(bool value);


// cmd_lst_utils_clean.c

/**
 * @brief Deletes a single command node from a linked list of commands.
 */
void	lst_delone_cmd(t_command *lst, void (*del)(void *));
/**
 * @brief Deletes all command nodes from a linked list of commands,
 * freeing their memory.
 */
void	lst_clear_cmd(t_command **lst, void (*del)(void *));


// fill_args_default.c


/// @brief Counts the number of arguments in a token list.
int	count_arguments(t_token *tmp);
/**
 * @brief Creates an argument list in default mode, allocating memory for the
 * list and its strings, and initializes the list with default values.
*/
int	create_args_default_mode(t_token **token_node, t_command *last_cmd);
/**
 * @brief Adds a new argument to an argument list in default mode, allocating
 * memory for the new argument and updating the list.
*/
int	add_args_default_mode(t_token **token_node, t_command *last_cmd);
/**
 * @brief Fills the arguments in the command structure (command->args)
 * It has two modes:
 * - The "echo mode" if the command is the builtin "echo".
 * - The default mode for all the other cases.
*/
int	fill_args(t_token **token_node, t_command *last_cmd);


// fill_args_echo.c

/**
 * @brief Creates an argument list for command "echo", allocating memory for
 * the list and its strings, and initializes the list values.
 */
int	create_args_echo_mode(t_token **token_node, t_command *last_cmd);
/**
 * @brief Adds a new argument to an argument list for command "echo",
 * allocating memory for the new argument and updating the list.
 */
int	add_args_echo_mode(t_token **token_node, t_command *last_cmd);


// fill_args_echo_utils.c

/**
 * @brief Joins multiple variable tokens into a single string, handling cases
 * where variables contain spaces.
 * ex: The strings -> "Hello" "  " "world" become = "Hello  world"
 */
char	*join_vars(t_token **token_node);
/**
 * @brief Counts the number of arguments in a token list.
 */
int	count_args(t_token *temp);
/**
 * @brief Copies arguments from a token list into a new array, allocating
 * memory for the array and its strings.
 */
char	**copy_in_new_tab(int len, char **new_tab, t_command *last_cmd,
		t_token *tmp);
/**
 * @brief Removes empty variable (not existing in env) arguments from a
 * token list.
 * if variable X does not exist in environment,
 *		'echo $X $X $X $USER' should print:
 *		'username' (not '  username')
 */
void	remove_empty_var_args(t_token **tokens);


// parse_append.c

/**
 * @brief Parses the append redirection operator (>>) and updates the command
 * structure accordingly.
 */
void	parse_append(t_command **last_cmd, t_token **token_lst);


// parse_heredoc.c


/**
 * @brief 1??????????????????????????????????????????????????????????
 */


// parse_heredoc_utils.c


/**
 * @brief 1??????????????????????????????????????????????????????????
 */


// parse_input.c


/**
 * @brief Removes the old file reference from the input/output file descriptors.
 */
bool	remove_old_file_ref(t_io_fds *io, bool infile);
/**
 * @brief Parses the input redirection operator (<) and updates the command
 * structure accordingly.
 */
void	parse_input(t_command **last_cmd, t_token **token_lst);

// parse_pipe.c


/**
 * @brief Parses the pipe operator (|) and updates the command structure
 * accordingly.
 */
void	parse_pipe(t_command **cmd, t_token **token_lst);


// parse_trunc.c


/**
 * @brief This function takes a file path as input and returns a relative path
 * if the input path is not absolute.
 * The function checks if the input path starts with a slash (/). If it does,
 * the function returns a duplicate of the input path using ft_strdup. If not,
 * the function creates a new path by concatenating the current working
 * directory (./) with the input file name using ft_strjoin.
 */
char	*get_relative_path(char *file_to_open);
/**
 * @brief Parses the truncation operator (>) and updates the command
 * structure accordingly.
 */
void	parse_trunc(t_command **last_cmd, t_token **token_lst);

// parse_word.c

/**
 * @brief Parses a word token from a token list, handling variables, commands,
 * and arguments. It checks if the token is a variable, command, or argument,
 * and updates the command structure accordingly. If the token is a variable,
 * it checks if it contains spaces and splits it into a command and arguments
 * if necessary. The function then updates the last command in the command list
 * with the parsed token, and returns a pointer to the next token in the list.
 *
*/
void	parse_word(t_command **cmds, t_token **token_lst);




/* ------------------------------ UTILS --------------------------------------*/

//clean_up.c

/// @brief Freeing each string and the table itself.
void	free_str_tab(char **tab);
/// @brief Free a pointer
void	free_ptr(void *ptr);
/// @brief Fres the input/output fd structure
void	free_io(t_io_fds *io);

// errors.c

/// @brief Joins two strings and freeing the previous one.
char	*join_strs(char *str, char *add);
/// @brief Prints an error message and exits the program.
int	errmsg_cmd(char *command, char *detail, char *error_message, int error_nb);
/// @brief Prints an error message unrelated to a specific command.
///			 Used in parsing to handle syntax errors
void	errmsg(char *errmsg, char *detail, int quotes);
/// @brief
int	usage_msg();

// init_data.c

/**
 * @brief
*/
bool	init_data(t_data *data, char **env);
/**
 * @brief
*/
void	init_io(t_command *cmd);

/* ------------------------------ DEBUGS --------------------------------------*/

// debug.c

void	print_cmd_args(t_command *cmd);
void	print_cmd_io(t_command *cmd);
void	print_cmd_list(t_data *data);
void	print_token_type(t_token *token, char *prefix);
void	print_token_list(t_token **tokens);

void	print_tokens(t_token *head);
t_token *get_first_node(t_token *node);

/* ------------------------------- ENV ---------------------------------------*/
int	env_var_count(char **env);
int	get_env_var_index(char **env, char *var);
char	*get_env_var_value(char **env, char *var);
bool	is_valid_env_var_key(char *var);

int	main(int ac, char **env);
void running(t_data *data);
void execute();

#endif
