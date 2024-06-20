CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
NAME		= minishell

SRCS_PATH	= ./sources/
OBJ_PATH	= ./objects/
INC_PATH	= ./includes/
LIBFT_PATH	= ./libft/
LIBFT		= $(LIBFT_PATH)libft.a

SRC		=	expander/identify_var	\
			expander/quotes_handler	\
			expander/quotes_remover	\
			expander/recover_value	\
			expander/replace_var 	\
			expander/var_expander_utils	\
			expander/var_expander	\
			lexer/check_if_var	\
			lexer/lexer_grammar	\
			lexer/parse_user_input	\
			lexer/token_lst_utils	\
			lexer/token_lst_utils_2	\
			lexer/tokenization	\
			lexer/tokenization_utils	\
			parser/cmd_lst_utils	\
			parser/cmd_lst_utils_clean	\
			parser/create_command	\
			parser/fill_args_default	\
			parser/fill_args_echo	\
			parser/fill_args_echo_utils	\
			parser/parse_append	\
			parser/parse_heredoc	\
			parser/parse_heredoc_utils	\
			parser/parse_input	\
			parser/parse_pipe	\
			parser/parse_trunc	\
			parser/parse_word	\
			utils/clean_up	\
			utils/errors	\
			utils/init_data	\
			debug/debug	\
			env/env	\
			execution/execute	\
			main	\

SRCS		= $(addsuffix .c, $(addprefix $(SRCS_PATH), $(SRC)))
OBJS		= $(SRCS:$(SRCS_PATH)%.c=$(OBJ_PATH)%.o)
INCS		= -I $(INC_PATH) -I $(LIBFT_PATH)

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/lexer
	mkdir -p $(OBJ_PATH)/expander
	mkdir -p $(OBJ_PATH)/parser
	mkdir -p $(OBJ_PATH)/utils
	mkdir -p $(OBJ_PATH)/debug
	mkdir -p $(OBJ_PATH)/env
	mkdir -p $(OBJ_PATH)/execution

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) -l readline

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
