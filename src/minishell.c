/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/15 16:12:14 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void run_cmd(t_token *head, char **env)
{
    int pid;

    pid = fork();
    if (!pid)
    {
        execve(head->args[0], head->args, env);
    }
    else
        wait(0);     
}
int main(int argc, char **argv, char **env)
{
    char    *line;
    char    **paths;
    t_list *envl ;

    (void)argc;
    (void)argv;
    (void)paths;
    paths = split_paths(get_PATH(env));
    envl= setup_env(env);
    // while (*paths)
    //     printf("%s\n", *paths++);
    while (1)
    {
        line = readline("Minishell$ ");
        if (line[0] == '\0')
            continue;
        // print the args
        t_token *head = init_tokens(line);
        add_t_type(head);
        split_args(head);
        // echo(head->args);
        // int i = 0;
        if (ft_strnstr(head->value, "exit", ft_strlen("exit")))
        {
            if (head->args[1] != NULL)
                exit(ft_atoi(head->args[1]));
        }
        run_cmd(head, env);
        // while (head)
        // {
        //     printf("#########################\n");
        //     printf("%i: Token => %s\n", i, head->value);
        //     if (head->args != NULL)
        //     {
        //         for (int i = 0; head->args[i]; i++)
        //         {
        //             printf("arg[%i] => %s\n", i, head->args[i]);
        //         }
        //     }
        //     else
        //         printf("args => %s\n", "NULL");
        //     printf("Type => %s\n", head->type);
        //     i++;
        //     head = head->next;
        // }
        add_history(line);
    }
    return (0);
}