/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:33:16 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/11 20:03:42 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parser.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*global variable*/
extern int	g_status;
/*error.c*/
void		error_func(int errnum, int exit_num);
void		error_exit(char *str, int exit_num);
void		error_and_exit(int exit_num);
void		execve_error(char *cmd);
/*builtin.c*/
void		echo(char **cmd);
void		print_env(t_list *envl);
int			cd(char **args, t_list **envl, t_list **exp_list, char *path);
char		*pwd(int i, t_list *envl);
void		export(t_list **exp_list, t_list **envl, char *var_name,
				char *var_value);
void		unset(t_list **envl, char *var_name, int flag);
t_list		*setup_env(char **env);
t_list		*setup_exp(t_list *envl);
char		*fenv(t_list *envl, char *str);
char		**convert_to_array(t_list *envl);
void		ft_exit(t_token *head);
void		init_export(t_token *head, t_list **envl, t_list **exp_list, int i);
void		change_var_and_free(char *var_name, char *var_value, char *str,
				t_list *tmpl);
int			check_var(char *var_name);
void		print_export(t_list *exp_list);
void		while_print_export(t_list *exp_list);
/*pipes.c*/
typedef struct s_pipe
{
	int		fd[2];
}			t_pipe;

int			exec_pipes(t_token *head, t_list **envl, t_list **exp_list,
				char **paths);
void		init_var_pipe(t_token *head, int i[5]);
void		next_cmd(t_token **head);
void		close_unused_fd(t_pipe *fdt, int p);
void		free_and_wait(t_pipe *fdt, int p, int pid);
int			calc_pipes(t_token *list);
/*exec.c*/
int			check_pipe(t_token *list);
void		run_cmd(t_token *head, t_list **envl, t_list **exp_list,
				char **paths);
char		*get_path(t_list *envl);
char		**split_paths(char *paths);
int			check_builtin(char *cmd);
void		run(t_token *head, t_list **envl, t_list **exp_list, char **paths);
char		*check_cmd(char *cmd, char **paths);
int			builtin(t_token *head, t_list **envl, t_list **exp_list);
void		printf_error(char *str, char *cmd, int exit_status);
void		free_run_cmd(char **paths, char **env, char ***arr, int flag);
char		**convert_to_array(t_list *envl);
void		excution(t_token **head, t_list **envl, t_list **exp_list);
/*redirection.c*/
int			redir_output(char *filename, int flag);
int			redir_input(char *filename);
int			check_redir(t_token *head, int f);
char		*last_io(t_token *head, int type);
void		redirection(t_token *head, t_list **envl, t_list **exp_list);
void		set_up_env_exp(t_list **envl, t_list **exp_list, char **env);
# ifndef DEFAULT_PATH_VALUE
#  define DEFAULT_PATH_VALUE "PATH=/nfs/homes/rbenmakh/.local/bin:\
	/nfs/homes/rbenmakh/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:\
	/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
# endif
#endif 