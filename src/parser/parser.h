#ifndef MINISHELL_H
#define MINISHELL_H

# include <fcntl.h>
#include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


char **check_cmds(char *line);
int count_words(char *line, char *set,int *i);
char **fill_arr(char **arr, char *line, int *i);

int count_words_2(char *line, char *set,int *i);
char **fill_arr_2(char **arr, char *line, int *i, char *set);
char **join_cmds(char **big, char **mini, int pos);

#endif
