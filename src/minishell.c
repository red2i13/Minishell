/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesssahraoui <younesssahraoui@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/19 17:22:07 by younesssahr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int status_code;

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

void p_cmd(t_token *head)
{
    int i = 0;
    while (head)
    {
        printf("#########################\n");
        printf("%i: Token => %s\n", i, head->value);
        if (head->args != NULL)
        {
            for (int i = 0; head->args[i]; i++)
            {
                printf("arg[%i] => (%s)\n", i, head->args[i]);
            }
        }
        else
            printf("args => (%s)\n", "NULL");
        printf("Type => %s\n", head->type);
        i++;
        head = head->next;
    }
}

int main(int argc, char **argv, char **env)
{
    char    *line;
    char    **paths;
    // t_list *envl ;

    (void)argc;
    (void)argv;
    (void)paths;
    paths = split_paths(get_PATH(env));
    // envl= setup_env(env);
    // while (*paths)
    //     printf("%s\n", *paths++);
    pid_t pid;
    while (1)
    {
        line = readline("Minishell$ ");
        pid = fork();
        if (!pid)
        {
            check_syntax(line);
            exit(0);
        }
        else
            wait(&status_code);
        printf("%i\n", WEXITSTATUS(status_code));
        if (line[0] == '\0')
            continue;
        // print the args
        t_token *head = init_tokens(ft_strtrim(line, " "));
        head = init_tokens(join_tokens(head));
        add_t_type(head);
        split_args(head);
        // echo(head->args);
        if (ft_strnstr(head->value, "exit", ft_strlen("exit")))
        {
            if (head->args[1] != NULL)
                exit(ft_atoi(head->args[1]));
        }
        // run_cmd(head, env);
        p_cmd(head);
        add_history(line);
    }
    return (0);
}