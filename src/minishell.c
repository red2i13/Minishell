/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/07 12:37:55 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    t_list  *envl ;
    t_list  *exp_list;

    (void)argc;
    (void)argv;
    signal_setup();
    envl= setup_env(env);
    exp_list = setup_exp(envl);
    //export(exp_list, envl, "SHLVL=", +1)
    while (1)
    {
        line = readline("Minishell$ ");
        //uncomment when finish debugging
        // pid = fork();
        // if (!pid)
        // {
        //     check_syntax(line);
        //     exit(0);
        // }
        // else
        //     wait(0);
        //printf("%i\n", WEXITSTATUS(status_code));
        //
        if(!line)
        {
            printf("Exit\n");
            ft_exit(0);
        }
        if (line[0] == '\0')
            continue;
        // print the args
        t_token *head = init_tokens(ft_strtrim(line, " "));
        head = init_tokens(join_tokens(head));
        add_t_type(head);
        split_args(head, envl);
        
        //DONE: add the function that run the command in while with the paths splited 
        //check if normal command or pipe
        if(check_pipe(head))
            exec_pipes(head, &envl, &exp_list, split_paths(get_PATH(envl)));
        else
            run_cmd(head, &envl, &exp_list,split_paths(get_PATH(envl)));
        //p_cmd(head);
        //UPDATE PWD : get the current path
        add_history(line);
    }
    return (0);
}
