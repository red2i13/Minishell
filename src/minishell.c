/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/10 10:53:46 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status;

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    t_token *head;
    t_list  *envl;
    int c_option_f;
    t_list  *exp_list;

    set_up_env_exp(&envl, &exp_list, env);
    c_option_f = 0;
    while (argc && argv)
    {
        signal_setup(2);
        restor_history(envl);
        if (c_option_f)
            return (g_status);
        if (argc == 3 && ff_strncmp("-c", argv[1], ft_strlen("-c")))
        {
            line = argv[2];
            c_option_f  = 1;
        }
        else
            line = prompt(envl);
        if (!line)
            return (ctl_exit(exp_list, envl));
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
        ex_rm(&head, envl);
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
