/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/29 18:15:25 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status;

void p_list(t_token *head)
{
    while (head)
    {
        printf("==========================\n");
        for (int i = 0; head->args[i]; i++)
        {
            printf("{%i}[%s]\n", i, head->args[i]);
        }
        printf("%i\n", head->arg_size);
        if (head->type == HEREDOC)
            printf("HEREDOC\n");
        if (head->type == RED)
            printf("RED\n");
        if (head->type == PIPE)
            printf("PIPE\n");
        if (head->type == CMD)
            printf("CMD\n");
        if (head->type == FILE_N)
            printf("FILE_N\n");
        printf("index = %i\n", head->index);
        printf("==========================\n");
        head = head->next;
    }
}

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    int i[3];
    t_token *head;
    t_list  *envl ;
    t_list  *exp_list;
    (void)argc;
    (void)argv;
    envl= setup_env(env);
    exp_list = setup_exp(envl);
    while (1)
    {
        if (!g_status)
            line = readline("\033[0;32mminishell →\033[0m ");
        else
            line = readline("\033[0;32mminishell\033[0;31m →\033[0m ");
        if (!line)
        {
            printf("exit\n");
            if(envl)
                ft_lstclear(&envl, &del);
            if(exp_list)
                ft_lstclear(&exp_list, &del);
            free(line);
            return (0);
        }
        if (line[0] == '\0' || count_words(line, " \t", i) == 0)
            continue;
        head = cmds_parse(line);
        heredoc(head, envl);
        start_ex(head, envl);
        start_rm_q(head);
        cmd_mk(head);
        ///////////////////////////////////////////////
        //p_list(head);
        ///////////////////////////////////////////////
        if (!head)
            continue;
        if(check_pipe(head))
            exec_pipes(head, &envl, &exp_list, split_paths(get_PATH(envl)));
        else if(check_redir(head, 0) || check_redir(head, 1))
        {
            int pid;
            int exit_st;
            if(!(pid = fork()))
            {
                //pick tha last input
                char *input = last_io(head, 1);
                if(input)
                    redir_input(input);
                run(head, &envl, &exp_list,split_paths(get_PATH(envl)));
                exit(0);
            }
            else
                wait(&exit_st);
            g_status = exit_st / 256;
        }
        else
            run_cmd(head, &envl, &exp_list,split_paths(get_PATH(envl)));
        list_clear(head);
        head = NULL;
    }
    return (0);
}
