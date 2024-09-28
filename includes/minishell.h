/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:41:26 by gabarnou          #+#    #+#             */
/*   Updated: 2024/09/28 21:28:06 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */


# include ".././libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>




/* ************************************************************************** */
/*                                  MACROS                                    */
/* ************************************************************************** */


# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define SUCCESS 0
# define FAILURE 1
# define CMD_NOT_FOUND 127

# define PROMPT "Mini_Inclusivite --> "
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"




/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */


typedef struct s_token
{
	char				*str;
	char				*str_backup;
	int					type;
	int					status;
	bool				var_exist;
	bool				join;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_io_fds
{
	char				*infile;
	char				*outfile;
	char				*delimiter;
	bool				heredoc_quotes;
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
}						t_io_fds;

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*path;
	bool				pipe_output;
	int					*pipe_fd;
	struct s_command	*prev;
	struct s_command	*next;
	t_io_fds			*io_fds;
	pid_t				pid;
}						t_command;

typedef struct s_data
{
	t_token				*token;
	char				*user_input;
	char				**env;
	char				*working_dir;
	char				*old_working_dir;
	int					last_exit_code;
	pid_t				pid;
	t_command			*cmd;
}						t_data;


/* ************************************************************************** */
/*                               ENUMERATIONS                                 */
/* ************************************************************************** */


enum					e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	HEREDOC_NO_EXPAND,
	APPEND,
	END
};

enum					e_quoting_status
{
	UNQUOTED,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};




/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */




/* ------------------------------- LEXER -------------------------------------*/

/* ---- tokenization ---- */
int						tokenization(t_data *data, char *str);

/* ---- tokenization_utils ---- */


int						save_separator(t_token **token_lst, char *str,
							int index, int type);
int						save_word(t_token **token_lst, char *str, int index,
							int start);
int						is_separator(char *str, int i);
int						set_status(int status, char *str, int i);
int						save_word_or_sep(int *i, char *str, int start,
							t_data *data);

/* ---- token_lst_utils ---- */

t_token					*lst_new_token(char *str, char *str_backup, int type,
							int status);
void					lst_add_back_token(t_token **alst, t_token *new_node);
void					lst_del_one_token(t_token *lst, void (*del)(void *));
void					lst_clear_token(t_token **lst, void (*del)(void *));

/* ---- token_lst_utils_2 ---- */

t_token					*insert_lst_between(t_token **head, t_token *to_del,
							t_token *insert);

/* ---- parse_user_input ---- */

bool					parse_user_input(t_data *data);

/* ----lexer_grammar ---- */

int						check_consecutives(t_token **token_lst);

/* ---- check_if_var ---- */

void					_variable_check(t_token **token_node);
int						check_if_var(t_token **token_lst);






/* ------------------------------ EXPANDER -----------------------------------*/

/* ---- var_expander ---- */

int						var_expander(t_data *data, t_token **token_lst);
char					*var_expander_heredoc(t_data *data, char *str);


/* ---- var_expander_utils ---- */

void					copy_var_value(char *new_str, char *var_value, int *j);
char					*get_new_token_string(char *oldstr, char *var_value,
							int newstr_size, int index);


/* ---- replace_var ---- */

int						replace_var(t_token **token_node, char *var_value,
							size_t *index);
char					*replace_str_heredoc(char *str, char *var_value,
							size_t index);


/* ---- identify_var ---- */

bool					is_var_friendly(char c);
int						var_length(char *str);
char					*identify_var(char *str);


/* ---- recover_value ---- */

char					*recover_value(t_token *token, char *str, t_data *data);


/* ---- quotes_remover ---- */

int						remove_quotes(t_token **token_node);






/* -------------------------------- PARSER -----------------------------------*/

/* ---- create_command ---- */

void					create_command(t_data *data, t_token *token);

/* ---- cmd_lst_utils ---- */

t_command				*lst_last_cmd(t_command *cmd);
void					lst_add_back_cmd(t_command **alst, t_command *new);
t_command				*lst_new_cmd(bool value);


/* ---- cmd_lst_utils_clean ---- */

void					lst_delone_cmd(t_command *lst, void (*del)(void *));
void					lst_clear_cmd(t_command **lst, void (*del)(void *));


/* ---- fill_args_default ---- */

int						count_arguments(t_token *tmp);
int						create_args_default_mode(t_token **token_node,
							t_command *last_cmd);
int						add_args_default_mode(t_token **token_node,
							t_command *last_cmd);
int						fill_args(t_token **token_node, t_command *last_cmd);


/* ---- fill_args_echo_ ---- */

int						create_args_echo_mode(t_token **token_node,
							t_command *last_cmd);
int						add_args_echo_mode(t_token **token_node,
							t_command *last_cmd);


/* ---- fill_args_echo_utils ---- */

char					*join_vars(t_token **token_node);
int						count_args(t_token *temp);
char					**copy_in_new_tab(int len, char **new_tab,
							t_command *last_cmd, t_token *tmp);
void					remove_empty_var_args(t_token **tokens);


/* ---- parse_append  ---- */

void					parse_append(t_command **last_cmd, t_token **token_lst);


/* ---- parse_heredoc ---- */

bool					get_heredoc(t_data *data, t_io_fds *io);
void					parse_heredoc(t_data *data, t_command **last_cmd,
							t_token **token_lst);


/* ---- parse_heredoc_utils ---- */

bool					fill_heredoc(t_data *data, t_io_fds *io, int fd);

/* ---- parse_input ---- */

bool					remove_old_file_ref(t_io_fds *io, bool infile);
void					parse_input(t_command **last_cmd, t_token **token_lst);


/* ---- parse_pipe.---- */

void					parse_pipe(t_command **cmd, t_token **token_lst);


/* ---- parse_trunc ---- */

char					*get_relative_path(char *file_to_open);
void					parse_trunc(t_command **last_cmd, t_token **token_lst);


/* ---- parse_word ---- */

void					parse_word(t_command **cmds, t_token **token_lst);






/* -------------------------------- UTILS ------------------------------------*/

/* ---- clean_up ---- */

void					free_str_tab(char **tab);
void					free_ptr(void *ptr);
void					free_io(t_io_fds *io);
void					free_data(t_data *data, bool clear_history);


/* ---- errors ---- */

char					*join_strs(char *str, char *add);
int						errmsg_cmd(char *command, char *detail,
							char *error_message, int error_nb);
void					errmsg(char *errmsg, char *detail, int quotes);
int						usage_msg(void);


/* ---- init_data --- */

bool					init_data(t_data *data, char **env);
void					init_io(t_command *cmd);


/* ---- exit--- */

void					exit_shell(t_data *data, int exno);


/* ---- exit--- */

void					ft_free_tab(void **tab);
char					**ft_multi_split(char const *s, const char *c);





/* --------------------------------- ENV -------------------------------------*/

/* ---- env --- */

int						length_env(char **env);
int						search_in_env(char *s, char **env, size_t len);
int						get_env_var_index(char **env, char *var);
char					*get_env_var_value(char **env, char *var);
bool					is_valid_env_var_key(char *var);

/* ---- env_set --- */

bool					set_env_var(t_data *data, char *key, char *value);
bool					remove_env_var(t_data *data, int index);






/* ------------------------------- BUILTINS ----------------------------------*/

/* ---- export ---- */

int						valid_arg(char *s);
int						env_modif(t_data *data, char *s);
int						export_perform(t_data *data, char **args);
int						export_builtin(t_data *data, char **args);

/* ---- cd ---- */

int						cd_builtin(t_data *data, char **args);

/* ---- unset ---- */

int						unset_builtin(t_data *data, char **args);

/* ---- echo ---- */

bool					is_flag(char *args);
void					print_args(char **args, bool flag_newline);
int						echo_builtin(t_data *data, char **args);

/* ---- env ---- */

int						print_env(t_data *data);
int						env_builtin(t_data *data, char **args);

/* ---- pwd ---- */

int						pwd_builtin(void);

/* ---- exit ---- */

int						exit_builtin(t_data *data, char **args);






/* ----------------------------- EXECUTING -----------------------------------*/

/* ---- executing ---- */
int						exec_builtins(t_data *data, t_command *cmd);
int						exec_command(t_data *data, t_command *cmd);
int						executing(t_data *data);

/* ---- childrens ---- */

int						wait_childrens(t_data *data);
int						create_childrens(t_data *data);

/* ---- exec_command ---- */

int						launch_command(t_data *data, t_command *cmd);
int						exec_with_path(t_data *data, t_command *cmd);
char					*get_cmd_path(t_data *data, char *command);
int						check_command(t_data *data, t_command *cmd);

/* ---- redirections_utils ---- */

void					close_fd(t_command *command, bool close_back);
void					close_pipes(t_command *command, t_command *skip_cmd);

/* ---- redirections ---- */

bool					io_fd_handler(t_io_fds *io_fds);
bool					io_fd_restore(t_io_fds *io_fds);
bool					pipes_handler(t_command *cmds, t_command *command);
bool					create_pipes(t_data *data);

/* ---- utils ---- */

bool					is_directory(char *dir);
bool					check_builtins(char *cmd);
char					*final_path(char *cmd, char **path_env);
char					*get_path_env(char **env, char *var);
char					**extract_path(t_data *data);

/* ---- prep executing ---- */

bool					check_infile_outfile(t_io_fds *io);

/* ---- signals ---- */

void					ctrlc_shell_wait(int sig);
void					signal_handler_wait(void);
void					new_line(int sig);
void					signal_handler_run(void);
void					sigquit_disapear(void);





void					running(t_data *data);

#endif
