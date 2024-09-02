/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:50:47 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/01 23:21:43 by rbenmakh         ###   ########.fr       */
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
    env = convert_to_array(*envl);
    if (ft_strnstr(head->args[0], "exit", ft_strlen("exit")))
    {
        free_arr(paths);
        free_arr(env);
        env = NULL;
        //free envl and exp list
        ft_exit(head);
    }
    else if(!builtin(head, envl, exp_list))
    {
        free_arr(paths);
        free(env);
        env = NULL;
        return ;
    }
    cmd = check_cmd(head->args[0], paths);
    if(!cmd)
        exit(127);

    else if(execve(cmd, head->args, env) == -1)
    {
        perror("minishell: ");
        exit(EXIT_FAILURE);
    }
    if(cmd != head->args[0])
        free(cmd);
    free_arr(paths);
    free_arr(env);
    exit(0);
}


// int exec_pipes(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
// {
//     int i;
//     int pid;
//     int exit_st;    
//     int p = calc_pipes(head);
//     int **fdt = init_pipes(p);
   
//     i = p;
//     while(head->next)
//     {
//         head = head->next;
//     }
//     while(i >= 0)
//     {
//         if(!(pid = fork()))
//         {
//             if(i != p)
//             {
//                 dup2(fdt[i][1], STDOUT_FILENO);
//             }
//             if(i > 0)
//             {
//                 dup2(fdt[i - 1][0], STDIN_FILENO);
//             }
//             //function that kill all the unused file descriptor
//             for(int k = 0; k < p; k++)
//             {
//                 close(fdt[k][0]);
//                 close(fdt[k][1]);
//             }
//             run(head, envl, exp_list, paths);
//             exit(0);
//         }
//         if(head->prev)
//             head = head->prev->prev;
//         i--;
//     }
//     for (i = 0; i < p; i++) 
//     {
//         close(fdt[i][0]);
//         close(fdt[i][1]);
//     }
//     while(wait(&exit_st) > 0)
//     {   
//         printf("status %i\n", WEXITSTATUS(exit_st));
//     }
//     for (i = 0; i < p; i++) 
//     {
//         free(fdt[i]);
//     }
//     free(fdt);
//     g_status = exit_st / 256;
//     free_arr(paths);
//     return(0);
// }

int exec_pipes(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    int i;
    int pid;
    int exit_st;    
    int p = calc_pipes(head);
    int **fdt = init_pipes(p);
    //to test
    int last_pid;
    i = 0;

    while(i <= p)
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
        }
        else if(i == p)
            last_pid = pid;
        if(head->next)
            head = head->next->next;
        i++;
    }
    for (i = 0; i < p; i++) 
    {
        close(fdt[i][0]);
        close(fdt[i][1]);
    }
    waitpid(last_pid, &exit_st, 0);
    while(wait(NULL) > 0)
    {
    }
    g_status = WEXITSTATUS(exit_st);
    for (i = 0; i < p; i++) 
    {
        free(fdt[i]);
    }
    free(fdt);
    free_arr(paths);
    return(0);
}
