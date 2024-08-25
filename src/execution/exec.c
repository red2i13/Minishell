/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:38:20 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/25 13:29:29 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *check_cmd(char *cmd, char **paths)
{
    int num; 
    int i ;
    char *tmp;
    
	i = 0;
    num = -1;
	if(!paths)
		return(NULL);
	else if(!access(cmd,F_OK | X_OK))
		return(cmd);
    while(paths[i])
    {
		tmp = ft_strjoin( "/", cmd);
        tmp = ft_strjoin(paths[i], tmp);
        num = access(tmp, F_OK | X_OK);
		if(!num)
			return(tmp);
		free(tmp);
        i++;
    }
	//if the command not found return 127 as exit code
    if(num == -1 && check_builtin(cmd))
	{
        //this function should store the exit code if the command is not found
		printf("$: command not found: %s\n", cmd);
		g_status = 127;
        //error_func(errno, 127);
        return(0);
	}
	return(cmd);
}
int check_redir(t_token *head, int f)
{
    while(head)
    {
        if(head->args[0][0] == '>' && !f)
        {
            if(head->args[1] == NULL)
                return(1);
            else
                return(2);
        }
        if(head->args[0][0] == '<' && f)
        {
            return(1);
        }
        head = head->next;
    }
    return(0);
}
void run_cmd(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    int pid;
    char *cmd;
    char **env ;
    (void)pid;
    int exit_st;
    
    exit_st = 0;
    env = convert_to_array(*envl);
    cmd = check_cmd(head->args[0], paths);
    if(!cmd)
        return ;
    if (ft_strnstr(head->args[0], "exit", ft_strlen("exit")))
            ft_exit(head);
    else if(ft_strnstr(head->args[0], "cd", 3))
        cd(head->args, envl, exp_list);
    else if(ft_strnstr(head->args[0], "echo", 5))
        echo(head->args);
    else if(ft_strnstr(head->args[0], "export", 7))
    {
        if(!head->args[1])
            export(exp_list, envl, NULL, NULL);
        init_export(head, envl, exp_list);

    }
    else if(ft_strnstr(head->args[0], "unset", 6))
    {
        unset(envl, head->args[1], 0);
        unset(exp_list, head->args[1], 1); 
    }
    else if(ft_strnstr(head->args[0], "env", 4))
        print_env(*envl);
    else if(ft_strnstr(head->args[0], "pwd", 4))
        pwd(1, *envl);
    else
    {
        pid = fork();
        if(!pid)
        {
            if(execve(cmd, head->args, env) != 0)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
            wait(&exit_st); 
    }
    g_status = exit_st / 256;
}
//funcitons for signals
void sighandler(int signum) 
{
    if(signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void signal_setup()
{
    signal(SIGINT, sighandler);
    signal(SIGQUIT, SIG_IGN);
    //signal(EOF, sighandler);
}
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