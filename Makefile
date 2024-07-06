#Dont forget to delet the -g flag
CFLAGS = -Wall -Wextra -Werror -g
FLAGS = -lreadline
FILES =  minishell.c parsing_utlis.c error.c lexer.c token_list_functions.c builtin.c
SOURCES = $(addprefix $(SRC_DIR)/, $(FILES))
OBJECTS = $(SOURCES:.c=.o)
NAME = minishell

CC = cc
LIB = libft
SRC_DIR = src
LIBFT_DIR = libft/include
INCLUDES = include

all: $(NAME) 

$(NAME): $(OBJECTS) libft/libft.a 
	$(CC) $(CFLAGS)  -I$(LIBFT_DIR) -I$(INCLUDES) -o $@ $^  $(FLAGS)

$(LIB)/libft.a:
	$(MAKE) -C $(LIB) all

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(INCLUDES) -c $< -o $@

clean:
	rm -f src/*.o
	$(MAKE) -C $(LIB) clean

fclean: clean
	rm -f minishell
	$(MAKE) -C $(LIB) fclean

re: fclean all

.PHONY: fclean clean re