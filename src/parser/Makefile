#Dont forget to delet the -g flag
CFLAGS = -g
FLAGS = -lreadline
SOURCES = main.c check_cmds.c  cmds_trim.c cmds_trim_2.c join_cmds.c
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
	$(MAKE) -C $(LIB) all bonus

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(INCLUDES) -c $< -o $@

clean:
	$(MAKE) fclean -C $(LIB) 
	rm -rf $(OBJECTS)