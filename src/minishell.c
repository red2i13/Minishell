/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/09 01:58:49 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int g_status;

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    int i[3];
    t_token *head;
    t_list  *envl ;
    t_list  *exp_list;
    (void)argc;
    (void)argv;
    char **args  ;
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
            return (0);
        }
        if (line[0] == '\0' || count_words(line, "     ", i) == 0)
            continue;
        head = cmds_parse(line);
        heredoc(head);
        if (!head)
            continue;
        args = get_cmds(line);
        if (!args)
            return (0);
        head = init_tokens(args);
        // while (head)
        // {
        //     for (int i = 0; head->args[i]; i++)
        //         printf("[%s] %i\n", head->args[i], i);
        //     printf("==========================\n");
        //     head = head->next;
        // }
        // exit(22);
        if(check_pipe(head))
            exec_pipes(head, &envl, &exp_list, split_paths(get_PATH(envl)));
        else if(check_redir(head) == 2 || check_redir(head) == 1)
        {
            int pid;
            if(!(pid = fork()))
            {
                run(head, &envl, &exp_list,split_paths(get_PATH(envl)));
                exit(0);
            }
            else
                wait(0);
        }
        else if(check_redir(head) == 3)
        {
            int pid1;
            if(!(pid1 = fork()))
            {
                redir_input(head->next->next->args[0]);
                run(head, &envl, &exp_list,split_paths(get_PATH(envl)));
                exit(0);
            }
            else
                wait(0);        
        }
        else
            run_cmd(head, &envl, &exp_list,split_paths(get_PATH(envl)));

    }
    return (0);
}
