#ifndef PARSER_H
#define PARSER_H

# include <fcntl.h>
#include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

/*enum for the type of the tokens*/
typedef enum e_type{
    PIPE = 1,
    RED,
    CMD
}t_type;

/*enum for the err*/
typedef enum e_err{
    PIPE_E = -3,
    RED_E,
    QUOTE_E,
}t_err;

/*linkd list*/
typedef struct s_token
{
    char    **args;
    t_type  type;
    int     arg_size;
    struct s_token  *next;
    struct s_token  *prev;
}       t_token;

char **get_cmds(char *line);
int count_words(char *line, char *set,int *i);
char **fill_arr(char **arr, char *line, int *i);

int count_words_2(char *line, char *set,int *i);
char **fill_arr_2(char **arr, char *line, int *i, char *set);
char **join_cmds(char **big, char **mini, int pos);


/*token_list_functions.c*/
void	add_back_t(t_token **head, t_token *new);
t_token *create_token(char **args);
size_t  size_list(t_token *head);
void    list_clear(t_token *head);
t_token *last_t(t_token *head);

t_token *init_tokens(char **args);
void set_size(t_token *head);
void set_type(t_token *head);

int check_err(t_token *head);
void p_err(t_err n);
t_token *cmds_parse(char *line);
#endif
