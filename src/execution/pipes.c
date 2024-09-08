/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:50:47 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/08 11:02:00 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
typedef struct s_pipe
{
    int fd[2];
} t_pipe;

int calc_pipes(t_token *list)
{
    int p;

    p = 0;
    while (list)
    {
        if(list->args[0] && list->args[0][0] == '|')
            p++;
        list = list->next; 
    }
    return(p);
}
t_pipe *init_pipes(int p)
{
    t_pipe *fdt;
    int i;

    i = 0;
    fdt = malloc(sizeof(t_pipe) * p);
    if(!fdt)
        return(0);
    while(i < p)
    {
        if(pipe(fdt[i].fd) == -1)
        {
            //exit if the pipes are note created 
            (void)fdt;
        }
        i++;
    }
 
    return(fdt);
}
void pipe_redirection(t_token *head)
{
    int r;
    if((r = check_redir(head, 0) || check_redir(head, 1)))
    {
        t_token *tmp = head;
        while(tmp)
        {
            if(tmp->args[0] && tmp->args[0][0] == '|')
                break;
            else if(tmp->args[0] && tmp->args[0][0] == '>')
                redir_output(tmp->next->args[0], r);
            else if(tmp->args[0] && tmp->args[0][0] == '<')
                redir_input(tmp->next->args[0]);
            tmp = tmp->next;
        }
    }
}
void check_invalid_cmd(t_token *head)
{
	if(!head->args[0] || 
    (head->args[0] && head->args[0][0] == '>') || 
    (head->args[0] && head->args[0][0] == '<'))
        exit(0);
}
void run(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    char    *cmd ;
    char    **env ;
    
    pipe_redirection(head);
    check_invalid_cmd(head);
    if (ft_strnstr(head->args[0], "exit", ft_strlen("exit")))
        ft_exit(head);
    else if(!builtin(head, envl, exp_list))
    {
        g_status = 0;
        exit(0);
    }
    env = convert_to_array(*envl);
    if(!(cmd = check_cmd(head->args[0], paths)))
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

void close_unused_fd(t_pipe *fdt, int p)
{
    int i = 0;
    
    while(i < p)
    {
        close(fdt[i].fd[0]);
        close(fdt[i].fd[1]);
        i++;
    }
}
void next_cmd(t_token **head)
{
    while (*head)
    {
        if((*head)->args[0] && (*head)->args[0][0] == '|')
        {
            *head = (*head)->next;
            break;
        }
        *head = (*head)->next;
    }
}  
void free_fdt(t_pipe *fdt, int p)
{
    // int i = 0;
    (void)p;
    // while(i < p)
    // {
        // free(fdt[i][0]);
        // free(fdt[i][1]);
        free(fdt);
    //     i++;
    // }
    // free(fdt);
    fdt = NULL;
}

void free_and_wait(t_pipe *fdt, int p, int pid)
{
    free_fdt(fdt, p);
    waitpid(pid, &p, 0);
    while(wait(NULL) > 0)
    {
    }
}   
int exec_pipes(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    int i[5]; 
    t_pipe *fdt = init_pipes(i[3]);

    i[0] = 0;
    i[3] = calc_pipes(head);
    while(i[0] <= i[3])
    {
        if(!(i[1] = fork()))
        {
            if(i[0] != i[3])
                dup2(fdt[i[0]].fd[1], STDOUT_FILENO);
            if(i[0] > 0)
                dup2(fdt[i[0] - 1].fd[0], STDIN_FILENO);
            //function that kill all the unused file descriptor
            close_unused_fd(fdt, i[3]);
            run(head, envl, exp_list, paths);
        }
        else if(i[0] == i[3])
            i[4] = i[1];
        next_cmd(&head);
        i[0]++;
    }
    close_unused_fd(fdt, i[3]);
    free_and_wait(fdt, i[3], i[4]);
    return (free_arr(paths), 0);
}
