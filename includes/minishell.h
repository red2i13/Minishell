/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:33:16 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/05 10:41:01 by ysahraou         ###   ########.fr       */
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
# include<stdlib.h>
# include <string.h>
# include <sys/wait.h>

/*linkd list*/
typedef struct s_token
{
    char    *value;
    char    *type;
    char    **args;
    struct s_token  *next;
    struct s_token  *prev;
}       t_token;


/*parsing_utils.c*/
char	**split_paths(char *paths);
char *check_cmd(char *cmd, char **paths);
char *get_PATH(char **env);
void	split_args(t_token *head);

/*error.c*/
void    error_func(int errnum, int exit_num);

/*token_list_functions.c*/
void	add_back_t(t_token **head, t_token *new);
t_token *create_token(char *value);
size_t	size_list(t_token *head);
void list_clear(t_token *head);

/*parser.c*/
t_token *init_tokens(char *cmd);
void add_t_type(t_token *head);

#endif