/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:38:20 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/09 03:10:37 by rbenmakh         ###   ########.fr       */
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
		//error_func(errno, 127);
	}
	return(0);
}
int check_redir(t_token *head)
{
    while(head)
    {
        if(head->args[0][0] == '>')
        {
            if(head->args[1] == NULL)
                return(1);
            else
                return(2);
        }
        if(head->args[0][0] == '<')
        {
            if(head->args[1] == NULL)
                return(3);
            else
                return(4);
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
    
    env = convert_to_array(*envl);
    cmd = check_cmd(head->args[0], paths);
    if (ft_strnstr(head->args[0], "exit", ft_strlen("exit")))
            ft_exit(head->args[1]);
    else if(ft_strnstr(head->args[0], "cd", 3))
        cd(head->args, envl, exp_list);
    else if(ft_strnstr(head->args[0], "echo", 5))
        echo(head->args);
    else if(ft_strnstr(head->args[0], "export", 7))
    {
        int i = 1;
        if(!head->args[1])
            export(exp_list, envl, NULL, NULL);
        while (head->args[i])
        {
            char *f ;
            f = NULL;
            if(head->args[i])
                f= ft_strchr(head->args[i], '=');
            char *var_value;
            char *var_name;
            
            var_name = NULL;
            var_value = NULL;
            if(!f && head->args[i])
            { 
                var_name = ft_substr(head->args[i], 0, ft_strlen(head->args[i]));
                //var_value = ft_strdup("");
            }
            else if(f && head->args[i])
            {
                var_name =  ft_substr(head->args[i], 0, f - head->args[i] + 1 );
                var_value = ft_strdup(ft_strchr(head->args[i], '=') + 1);
            }
            export(exp_list,envl,var_name, var_value);
            i++;
        }
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
            if(execve(cmd, head->args, env) == -1)
            {
                //use perror of strerror function
                //perror("Error ");
                // char *error = strerror(errno);
                // printf("debug %s\n", error);
                exit(127);
            }
        }
        else
            wait(0);  
    }
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