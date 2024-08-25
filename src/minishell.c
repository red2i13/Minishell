/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/25 13:27:32 by rbenmakh         ###   ########.fr       */
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
            free(line);
            return (0);
        }
        if (line[0] == '\0' || count_words(line, "     ", i) == 0)
            continue;
        head = cmds_parse(line);
        heredoc(head, envl);
        start_ex(head, envl);
        start_rm_q(head);
        if (!head)
            continue;
        args = get_cmds(line);
        if (!args)
            return (0);
       // head = init_tokens(args);
        // while (head)
        // {
        //     for (int i = 0; head->args[i]; i++)
        //         printf("[%s] %i\n", head->args[i], i);
        //     printf("==========================\n");
        //     head = head->next;
        // }
   
        if(check_pipe(head))
            exec_pipes(head, &envl, &exp_list, split_paths(get_PATH(envl)));
        else if(check_redir(head, 0) || check_redir(head, 1))
        {
            int pid;
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
                wait(0);
        }
        else
            run_cmd(head, &envl, &exp_list,split_paths(get_PATH(envl)));

    }
    return (0);
}
