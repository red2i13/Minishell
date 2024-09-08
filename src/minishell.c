/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/08 15:14:05 by rbenmakh         ###   ########.fr       */
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
            printf("{%i}[%s]\n", i, head->args[i]);
        if (head->arg_size == 0)
            printf("{}[none]\n");
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
    t_token *head;
    t_list  *envl ;
    t_list  *exp_list;

    (void)argc;
    (void)argv;
    envl= setup_env(env);
    exp_list = setup_exp(envl);
    //update the shell level(make in a function)
    if(envl)
    {
        char *tmp ;
        char *val = ft_itoa(ft_atoi(tmp = get_var("SHLVL", envl)) + 1);
        free(tmp);
        export(&exp_list, &envl, "SHLVL=", val);
        free(val);
    }
    //
    //if env is empty
    if (envl == NULL)
    {
        char *tmp;
        export(&exp_list, &envl, "PWD=", tmp = getcwd(NULL, 0));
        export(&exp_list, &envl, "SHLVL=", "1");
        export(&exp_list, &envl, "_=", "/usr/bin/env");     
        free(tmp);
    }
    while (1)
    {
        signal_setup(2);
        restor_history(envl);
        line = prompt(envl);
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
        if (line[0] == '\0')
            continue;
        head = cmds_parse(line, envl);
        if (heredoc(head, envl) == 0)
        {
            list_clear(head);
            head = NULL;
            g_status = 130;
            continue;
        }
        start_ex(head, envl);
        rm_em_var(head);
        start_rm_q(head);
        while(1)
            if (cmd_mk(head))
                break;
        cmd_mk_v2(&head);
        set_type(head);
        set_size(head);
        ///////////////////////////////////////////////
        // p_list(head);
        ///////////////////////////////////////////////
        if (!head)
            continue;
        else if(check_pipe(head))
            exec_pipes(head, &envl, &exp_list, split_paths(get_path(envl)));
        else if(check_redir(head, 0) || check_redir(head, 1))
            redirection(head, &envl, &exp_list);
        else
            run_cmd(head, &envl, &exp_list,split_paths(get_path(envl)));
        list_clear(head);
        head = NULL;
    }
    return (0);
}
