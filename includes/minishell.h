/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:33:16 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/07 12:36:36 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parser.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>

/*linkd list*/
typedef struct s_token
{
    char    **args;
    char    *type;
    int    q;
    struct s_token  *next;
    struct s_token  *prev;
}       t_token;

/*error.c*/
void    error_func(int errnum, int exit_num);
void    error_exit(char *str, int exit_num);

/*builtin.c*/
void    echo(char **cmd);
void    print_env(t_list *envl);
int     cd(char **args, t_list **envl, t_list **exp_list);
char*   pwd(int i);
void export(t_list **exp_list, t_list**envl ,char *var_name, char *var_value);
void    unset(t_list **envl, char *var_name, int flag);
t_list  *setup_env(char **env);
t_list  *setup_exp(t_list   *envl);
char    *fenv(t_list    *envl, char *str);
char **convert_to_array(t_list *envl);
void    ft_exit(char *val);

/*pipes.c*/
int exec_pipes(t_token *head, t_list **envl, t_list **exp_list ,char **paths);

#endif