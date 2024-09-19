/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:50:31 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/19 12:48:38 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

/*enum for the type of the tokens*/
typedef enum e_type
{
	PIPE = 1,
	RED,
	CMD,
	HEREDOC,
	FILE_N
}					t_type;

/*enum for the err*/
typedef enum e_err
{
	PIPE_E = -3,
	RED_E,
	QUOTE_E,
}					t_err;

/*linkd list*/
typedef struct s_token
{
	char			**args;
	t_type			type;
	int				arg_size;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

char				**get_cmds(char *line, t_list *envl);
int					count_words(char *line, char *set, int *i);
char				**fill_arr(char **arr, char *line, int *i);
int					count_words_2(char *line, char *set, int *i);
char				**fill_arr_2(char **arr, char *line, int *i, char *set);
char				**join_cmds(char **big, char **mini, int pos);
void				add_front_t(t_token **head, t_token *new);
void				add_back_t(t_token **head, t_token *new);
t_token				*create_token(char **args);
size_t				size_list(t_token *head);
void				list_clear(t_token **head);
t_token				*last_t(t_token *head);

t_token				*init_tokens(char **args);
void				set_size(t_token *head);
void				set_type(t_token *head);

int					check_err(t_token *head);
void				p_err(t_err n);
t_token				*cmds_parse(char *line, t_list *envl);

int					heredoc(t_token *head, t_list *list[2], t_token *tmp,
						int status);
void				free_arr(char **arr);

char				*expand(char *str, t_list *env, int *q, char ***temp);
char				*vars_sub(char *str, int i, t_list *env);
void				start_ex(t_token *head, t_list *env, int q[4],
						char ***temp);

int					is_q(char *str);
void				start_rm_q(t_token *head);
char				*rm_quote(char *str);

int					cmd_mk(t_token *head);
void				set_index(t_token *head);
char				**ft_realloc(char *arg, char **old_arr);
void				del(void *c);

void				signal_setup(int n);
void				sig_exit(int num);
void				sighandler(int signum);
char				*get_var(char *str, t_list *env);
int					setup_h(char *line, t_list *envl);
void				restor_history(t_list *envl);
void				cmd_mk_v2(t_token **head);
void				fun_init(char ***new_args, t_token **head, char **args,
						int *i);
void				fun_init_v2(char ***new_args, t_token **head, char **args,
						int *i);
void				fork_heredoc(char *fn, t_token *head, t_list *list[2],
						t_token *tmp);
void				free_re(t_token *head, char *file_name);
int					ff_strncmp(const char *s1, const char *s2, size_t n);
void				free_expand(char *fr, char *brev, char *var, char *str);
char				*expand(char *str, t_list *env, int *q, char ***temp);
void				rm_em_var(t_token *head);
char				*prompt(t_list *env);
void				ex_rm(t_token **head, t_list *envl);
int					ctl_exit(t_list *exp_list, t_list *envl);
int					cmd_mk_2(t_token *head);
int					arr_size(char **arr);
char				*expand_h(char *str, t_list *env, int *q, char ***temp);
#endif
