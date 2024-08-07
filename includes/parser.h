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

/*linkd list*/
typedef struct s_token
{
    char    **args;
    char    *type;
    int    q;
    struct s_token  *next;
    struct s_token  *prev;
}       t_token;

char **check_cmds(char *line);
int count_words(char *line, char *set,int *i);
char **fill_arr(char **arr, char *line, int *i);

int count_words_2(char *line, char *set,int *i);
char **fill_arr_2(char **arr, char *line, int *i, char *set);
char **join_cmds(char **big, char **mini, int pos);


/*token_list_functions.c*/
void	add_back_t(t_token **head, t_token *new, int q);
t_token *create_token(char **args);
size_t  size_list(t_token *head);
void    list_clear(t_token *head);
t_token *last_t(t_token *head);

t_token *init_tokens(char **args);

#endif
