/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/08 18:36:45 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    char **args;
    t_token *head;

    (void)argc;
    (void)argv;
    (void)env;
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
        while (head)
        {
            for (int i = 0; head->args[i]; i++)
                printf("[%s]\n", head->args[i]);
            printf("==========================\n");
            head = head->next;
        }
    }
    return (0);
}
