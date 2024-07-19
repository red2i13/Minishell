/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:33:16 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/19 12:56:42 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

/*linkd list*/
typedef struct s_token
{
    char    *value;
    char    *type;
    char    **args;
    int    q;
    struct s_token  *next;
    struct s_token  *prev;
}       t_token;


/*parsing_utils.c*/
char    **split_paths(char *paths);
char    *check_cmd(char *cmd, char **paths);
char    *get_PATH(char **env);
void    split_args(t_token *head);

/*error.c*/
void    error_func(int errnum, int exit_num);
void    error_exit(char *str, int exit_num);

/*token_list_functions.c*/
void	add_back_t(t_token **head, t_token *new, int q);
t_token *create_token(char *value);
size_t  size_list(t_token *head);
void    list_clear(t_token *head);
t_token *last_t(t_token *head);

/*lexer.c*/
t_token *init_tokens(char *cmd);
void    add_t_type(t_token *head);
char *join_tokens(t_token *head);

/*builtin.c*/
void    echo(char **cmd);
void    print_env(t_list *envl);
int     cd(char **args, t_list **envl, t_list **exp_list);
char*   pwd(int i);
void export(t_list **exp_list, t_list**envl ,char *var_name, char *var_value);
void    unset(t_list **envl, char *var_name);
t_list  *setup_env(char **env);
t_list  *setup_exp(t_list   *envl);
char    *fenv(t_list    *envl, char *str);
char **convert_to_array(t_list *envl);
void    ft_exit(char *val);

/*checker.c*/
void    check_syntax(char *line);

#endif