/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:50:47 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/08/29 15:20:54 by rbenmakh         ###   ########.fr       */
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
    char *cmd;
    char **env ;
    
    cmd = check_cmd(head->args[0], paths);
    int r;
    if((r = check_redir(head, 0)))
    {
        t_token *tmp = head;
        while(tmp)
        {
            if(tmp->args[0][0] == '>')
                redir_output(tmp->next->args[0], r);
            tmp = tmp->next;
        }
    }
    if(!cmd)
        exit(127);
    env = convert_to_array(*envl);
    if (ft_strnstr(head->args[0], "exit", ft_strlen("exit")))
            ft_exit(head);
    else if(ft_strnstr(head->args[0], "cd", 3))
        cd(head->args, envl, exp_list);
    else if(ft_strnstr(head->args[0], "echo", 5))
        echo(head->args);
    else if(ft_strnstr(head->args[0], "pwd", 4))
        pwd(1, *envl);
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
    else if(execve(cmd, head->args, env) == -1)
    {
        perror("minishell: ");
        exit(EXIT_FAILURE);
    }
    free_arr(paths);
    free_arr(env);
}


int exec_pipes(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    int i;
    int pid;
    int exit_st;    
    int p = calc_pipes(head);
    int **fdt = init_pipes(p);
   
    i = p;
    while(head->next)
    {
        head = head->next;
    }
    while(i >= 0)
    {
        if(!(pid = fork()))
        {
            if(i != p)
            {
                dup2(fdt[i][1], STDOUT_FILENO);
            }
            if(i > 0)
            {
                dup2(fdt[i - 1][0], STDIN_FILENO);
            }
            //function that kill all the unused file descriptor
            for(int k = 0; k < p; k++)
            {
                close(fdt[k][0]);
                close(fdt[k][1]);
            }
            run(head, envl, exp_list, paths);
            exit(0);
        }
        if(head->prev)
            head = head->prev->prev;
        i--;
    }
    for (i = 0; i < p; i++) 
    {
        close(fdt[i][0]);
        close(fdt[i][1]);
    }
    while(wait(&exit_st) > 0)
    {   
    }
    for (i = 0; i < p; i++) 
    {
        free(fdt[i]);
    }
    free(fdt);
    g_status = exit_st / 256;

    return(0);
}