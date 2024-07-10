/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/10 22:13:29 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
TODO LIST:
-fix the redirection <<
- add a tty dedection interactive mode or non interactive mode
- fix the parsing
*/
int main(int argc, char **argv, char **env)
{
    char    *line;
    char    **paths;

    (void)argc;
    (void)argv;
    (void)paths;
    paths = split_paths(get_PATH(env));
    // while (*paths)
    //     printf("%s\n", *paths++);
    while (1)
    {
        line = readline("Minishell$ ");
        if (line[0] == '\0')
            continue;
        // print the args
        t_list *envl = setup_env(env);
        export(&envl, 0, 0);
        export(&envl, "SHLVL=", "455");
        printf("-----------------------------------------------------\n");
        unset(&envl, "SHLVL");
        export(&envl, 0, 0);
        
        exit(3);
        t_token *head = init_tokens(line);
        add_t_type(head);
        split_args(head);
        //test    
        int i = 0;
        while (head)
        {
            printf("#########################\n");
            printf("%i: Token => %s\n", i, head->value);
            if (head->args != NULL)
            {
                for (int i = 0; head->args[i]; i++)
                {
                    printf("arg[%i] => %s\n", i, head->args[i]);
                }
            }
            else
                printf("args => %s\n", "NULL");
            printf("Type => %s\n", head->type);
            i++;
            head = head->next;
        }
        //end of test
        add_history(line);
    }
    return (0);
}