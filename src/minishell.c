#include "../includes/minishell.h"

int main()
{
    char *cmd;
    char **tab;

    cmd = readline("minishell_$ ");
    tab = ft_split(cmd, ' ');

    return(0);
}