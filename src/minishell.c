/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/15 21:36:09 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void run_cmd(t_token *head, t_list **envl, char **paths)
{
    int pid;
    char *cmd;
    char **env ;
    
    env= convert_to_array(*envl);
    //make exit function with 2 states run in child and in the main process
    cmd = check_cmd(head->args[0], paths);
    // if(!cmd)
    //     return ;
    //printf("dubuug %s\n", head->args[0]);
    pid = fork();
    if (!pid)
    {
        if(ft_strnstr(head->args[0], "cd", 3))
            cd(head->args, envl);
        // else if(ft_strnstr(head->args[0], "echo", 5))
        //     echo("test");
        else if(ft_strnstr(head->args[0], "export", 7))
            export(envl, head->args[1], head->args[2]);
        else if(ft_strnstr(head->args[0], "unset", 6))
            unset(envl, head->args[1]);
        else if(ft_strnstr(head->args[0], "env", 4))
            print_env(*envl);
        else
            execve(cmd, head->args, env);
    }
    else
        wait(0);  
}
int main(int argc, char **argv, char **env)
{ 
    char    *line;
    char    **paths;
    t_list  *envl ;

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
        // for(int k = 0;head->args[k]; k++)
        // {
        //     printf("t: %s\n", head->args[k]);
        // }
        //DONE: add the function that run the command in while with the paths splited 
        run_cmd(head, &envl, split_paths(get_PATH(env)));
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