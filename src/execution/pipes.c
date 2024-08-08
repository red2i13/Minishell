/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:50:47 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/08/08 22:29:01 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int calc_pipes(t_token *list)
{
    int p;

    p = 0;
    while (list)
    {
        if(list->args[0][0] == '|')
            p++;
        list = list->next; 
    }
    return(p);
}
int **init_pipes(int p)
{
    int **fdt;
    int i;

    i = 0;
    fdt = (int**)malloc(sizeof(int*) * p);
    if(!fdt)
        return(0);
    while(i < p)
    {
        fdt[i] = malloc(sizeof(int) * 2);
        if(pipe(fdt[i]) == -1)
        {
            //exit if the pipes are note created 
            (void)fdt;
        }
        i++;
    }
 
    return(fdt);
}

void run(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
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
    else if(execve(cmd, head->args, env) == -1)
    {
        //use perror of strerror function
        //perror("Error ");
        // char *error = strerror(errno);
        // printf("debug %s\n", error);
        exit(127);
    }
}
int exec_pipes(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    int i;
    int pid;
    //int status;    
    int p = calc_pipes(head);
    int **fdt = init_pipes(p);
   
    i = 0; 
    while(i <= p)
    {
        if(!(pid = fork()))
        {
            if(i != p)
            {
                dup2(fdt[i][1], STDOUT_FILENO);
                close(fdt[i][0]);
                close(fdt[i][1]);
            }
            if(i > 0)
            {
                dup2(fdt[i-1][0], STDIN_FILENO);
                close(fdt[i -1][0]);
            }
            run(head, envl, exp_list, paths);
            exit(0);
        }
        else
        {
            if (i > 0)
                close(fdt[i - 1][0]);
            if(i < p)
                close(fdt[i][1]);  
        }
        if(head->next)
            head = head->next->next;
        i++;
    }
    while(wait(0) == 0)
    {   
    }
    return(0);
}

