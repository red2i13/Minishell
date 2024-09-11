#Dont forget to delet the -g flag
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
FLAGS = -lreadline
PARSER =   get_cmds.c cmds_trim_2.c cmds_trim.c join_cmds.c \
			token_list_functions.c init_tokens.c cmds_parse.c \
			parsing_utlis.c heredoc.c utiles.c expand.c rm_quote.c \
			signals.c history.c get_next_line_utils.c get_next_line.c \
			init_tokens_v2.c heredoc_v2.c expand_v2.c init_tokens_v2.c \
			token_list_functions_v2.c rm_not_valid_var.c prompt.c \
			parse_utiles.c utiles2.0.c
EXEC = builtin.c builtin1.c builtin2.c builtin3.c builtin_utils.c \
		exec.c exec1.c pipes.c pipe1.c pipe_utils.c redirection.c \
		set_up_env.c
HANDLE_ERR = check_err.c error.c
SOURCES = src/minishell.c
SOURCES += $(addprefix $(SRC_DIR_P)/, $(PARSER))
SOURCES += $(addprefix $(SRC_DIR_E)/, $(EXEC))
SOURCES += $(addprefix src/handle_err/, $(HANDLE_ERR))
OBJECTS = $(SOURCES:.c=.o)
NAME = minishell

CC = cc
LIB = libft
SRC_DIR_P = src/parser
SRC_DIR_E = src/execution
LIBFT_DIR = libft/include
INCLUDES = include



all: $(NAME)
	@echo "\033[0;31m";
	@echo "🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥";
	@echo "                                                    ";
	@echo " ██    ██ █ ██    █ █ █████ █   █ █████ █     █     ";
	@echo " ███  ███ █ ███   █ █ █     █   █ █     █     █     ";
	@echo " █ ████ █ █ █ ██  █ █ █████ █████ ████  █     █     ";
	@echo " █  ██  █ █ █  ██ █ █     █ █   █ █     █     █     ";
	@echo " █      █ █ █   ███ █ █████ █   █ █████ █████ █████ ";
	@echo "                                                    ";
	@echo "🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥";
	@echo "                                                    ";
	@echo "\033[0;32mMinishell is ready 🐚\033[0m";

$(NAME): $(OBJECTS) libft/libft.a
	@echo "\033[0;32mLinking obj files 🔗\033[0m"
	@$(CC) $(CFLAGS)  -I$(LIBFT_DIR) -I$(INCLUDES) -o $@ $^  $(FLAGS)

$(LIB)/libft.a:
	@echo "\033[0;32mCommpiling libft 📚\033[0m"
	@$(MAKE) -C $(LIB) all bonus -s

%.o: %.c
	@clear
	@echo "\033[0;32mCommpiling Minishell obj files ⏳\033[0m"
	@sleep 0.01
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(INCLUDES) -c $< -o $@

clean:
	@echo "\033[0;31mCleaning obj files 🗑️\033[0m"
	@rm -f $(OBJECTS)
	@$(MAKE) -C $(LIB) clean -s

fclean: clean
	@echo "\033[0;31mCleaning obj files and minishell program 🗑️\033[0m"
	@rm -f minishell
	@$(MAKE) -C $(LIB) fclean -s

re: fclean all

.PHONY: fclean clean re