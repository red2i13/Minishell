/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:38:20 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/05 11:54:53 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void printf_error(char *str, char *cmd)
{
    write(2, cmd, ft_strlen(cmd));
    write(2, ": ", 2);
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
}
char *check_cmd(char *cmd, char **paths)
{
    int num; 
    int i ;
    char *tmp;
    char *tmp1;
    
	i = 0;
    num = -1;
	if(!paths)
    {
        write(2, "minishell: : No such file or directory\n", 40);
        return(NULL);
    }
    else if(cmd[0] == '\0')
		return(NULL);
    else if(cmd[0] == '.' && access(cmd, F_OK) != 0)
    {
        printf_error("No such file or directory", cmd);
        g_status = 127;
        return(NULL);
    }
    while(paths[i])
    {
		tmp = ft_strjoin( "/", cmd);
        tmp1 = tmp;
        tmp = ft_strjoin(paths[i], tmp);
        free(tmp1);
        num = access(tmp, F_OK | X_OK);
		if(!num)
			return(tmp);
		free(tmp);
        i++;
    }
	if(!access(cmd,F_OK | X_OK))
		return(cmd);
	//if the command not found return 127 as exit code
    if(num == -1 && check_builtin(cmd))
	{
        //this function should store the exit code if the command is not found
		printf_error("command not found ", cmd);
		cmd = NULL ;
        g_status = 127;
	}
	return(cmd);
}
int check_redir(t_token *head, int f)
{
    while(head)
    {
        if(head->args[0][0] == '>' && !f)
            return(head->arg_size);
        if(head->args[0][0] == '<' && f)
        {
            return(1);
        }
        head = head->next;
    }
    return(0);
}
int builtin(t_token *head, t_list **envl, t_list **exp_list)
{
    if(!ft_strncmp(head->args[0], "cd", 3))
        return(cd(head->args, envl, exp_list), 0);
    else if(!ft_strncmp(head->args[0], "echo", 5))
        return(echo(head->args), 0);
    else if(!ft_strncmp(head->args[0], "export", 7))
    {
        if(!head->args[1])
            export(exp_list, envl, NULL, NULL);
        init_export(head, envl, exp_list);
        return(0);
    }
    else if(!ft_strncmp(head->args[0], "unset", 6))
    {
        unset(envl, head->args[1], 0);
        unset(exp_list, head->args[1], 1); 
        return(0);
    }
    else if(!ft_strncmp(head->args[0], "env", 4) && !head->args[1])
        return(print_env(*envl), 0);
    else if(!ft_strncmp(head->args[0], "env", 4) && head->args[1])
        return(write(2, "env: too many arguments\n", 25),0);
    else if(!ft_strncmp(head->args[0], "pwd", 4) && !head->args[1])
        return(pwd(1, *envl), 0);
    else if(!ft_strncmp(head->args[0], "pwd", 4) && head->args[1])
        return(write(2, "pwd: too many arguments\n", 25),0);        
    return(1);
}
void run_cmd(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    int pid;
    char *cmd;
    char **env;
    (void)pid;
    int exit_st;
    
    exit_st = 0;
    if(head->args[0][0] == '>' || head->args[0][0] == '<')
    {
        free_arr(paths);
        return ;
    }
    env = convert_to_array(*envl);
    if (!ft_strncmp(head->args[0], "exit", 5))
    {
        free_arr(paths);
        free_arr(env);
        env = NULL;
        //free envl and exp list
        ft_exit(head);
    }
    else if(!builtin(head, envl, exp_list))
    {
        g_status = 0;
        free_arr(paths);
        free(env);
        env = NULL;
        return ;
    }
    cmd = check_cmd(head->args[0], paths);
    if(!cmd)
    {
        free_arr(paths);
        free(env);
        env = NULL;
        return ;
    }
    else
    {
        signal_setup(0);
        pid = fork();
        if(!pid)
        {
            signal_setup(1);
            if(execve(cmd, head->args, env) != 0)
            {
                if(access(cmd, F_OK) == 0)
                    write(2, "minishell: is a directory\n", 27);
                //perror("minishell: ");
                exit(EXIT_FAILURE);
            }
        }
        else
            wait(&exit_st); 
    }
    g_status = exit_st / 256;
    free_arr(paths);
    if(cmd != head->args[0])
        free(cmd);
    free(env);
    env = NULL;
}
//funcitons for signals

int check_pipe(t_token *list)
{
    while(list)
    {
        if(list->args[0][0] == '|')
            return(1);
        list = list->next;
    }
    return(0);
}