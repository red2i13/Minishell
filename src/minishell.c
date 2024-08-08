/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/08 22:27:44 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    char **args;
    t_token *head;
    t_list  *envl ;
    t_list  *exp_list;
    (void)argc;
    (void)argv;
    
    envl= setup_env(env);
    exp_list = setup_exp(envl);
    while (1)
    {
        line = readline("Minishell$ ");
        if (!line)
        {
            printf("exit\n");
            return (0);
        }
        if (line[0] == '\0')
            continue;
        args = get_cmds(line);
        if (!args)
            return (0);
        head = init_tokens(args);
        // while (head)
        // {
        //     for (int i = 0; head->args[i]; i++)
        //         printf("[%s]\n", head->args[i]);
        //     printf("==========================\n");
        //     head = head->next;
        // }
        if(check_pipe(head))
            exec_pipes(head, &envl, &exp_list, split_paths(get_PATH(envl)));
        else
            run_cmd(head, &envl, &exp_list,split_paths(get_PATH(envl)));

    }
    return (0);
}
