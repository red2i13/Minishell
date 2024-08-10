/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/10 15:45:41 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int g_status;

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    int i[3];
    t_token *head;

    (void)argc;
    (void)argv;
    (void)env;
    while (1)
    {
        if (!g_status)
            line = readline("\033[0;32mminishell →\033[0m ");
        else
            line = readline("\033[0;32mminishell\033[0;31m →\033[0m ");
        if (!line)
        {
            printf("exit\n");
            return (0);
        }
        if (line[0] == '\0' || count_words(line, "     ", i) == 0)
            continue;
        head = cmds_parse(line);
        if (!head)
            continue;
        while (head)
        {
            for (int i = 0; head->args[i]; i++)
            {
                printf("[%s]\n", head->args[i]);
            }
            printf("%i\n", head->arg_size);
            printf("%i\n", head->type);
            printf("==========================\n");
            head = head->next;
        }
    }
    return (0);
}
