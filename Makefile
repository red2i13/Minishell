#Dont forget to delet the -g flag
CFLAGS = -Wall -Wextra -Werror -g
FLAGS = -lreadline
PARSER = get_cmds.c cmds_trim_2.c cmds_trim.c join_cmds.c token_list_functions.c init_tokens.c parsing_utlis.c
EXEC = builtin.c exec.c pipes.c redirection.c 
SOURCES = src/minishell.c src/handle_err/error.c

SOURCES += $(addprefix $(SRC_DIR_P)/, $(PARSER))
SOURCES += $(addprefix $(SRC_DIR_E)/, $(EXEC))

OBJECTS = $(SOURCES:.c=.o)
NAME = minishell

CC = cc
LIB = libft
SRC_DIR_P = src/parser
SRC_DIR_E = src/execution
LIBFT_DIR = libft/include
INCLUDES = include

all: $(NAME) 

$(NAME): $(OBJECTS) libft/libft.a 
	$(CC) $(CFLAGS)  -I$(LIBFT_DIR) -I$(INCLUDES) -o $@ $^  $(FLAGS)

$(LIB)/libft.a:
	$(MAKE) -C $(LIB) all bonus -s

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIB) clean -s

fclean: clean
	rm -f minishell
	$(MAKE) -C $(LIB) fclean -s

re: fclean all

.PHONY: fclean clean re