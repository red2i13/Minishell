/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/25 12:25:31 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int g_status;

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    int i[3];
    t_token *head;
    t_list  *envl;

    (void)argc;
    (void)argv;
    envl= setup_env(env);
    while (1)
    {
        if (!g_status)
            line = readline("\033[0;32mminishell →\033[0m ");
        else
            line = readline("\033[0;32mminishell\033[0;31m →\033[0m ");
        if (!line)
        {
            printf("exit\n");
            free(line);
            return (0);
        }
        if (line[0] == '\0' || count_words(line, "     ", i) == 0)
            continue;
        head = cmds_parse(line);
        if (!head)
            continue;
        heredoc(head, envl);
        start_ex(head, envl);
        start_rm_q(head);
        list_clear(head);
        head = NULL;
        while (head)
        {
            printf("==========================\n");
            for (int i = 0; head->args[i]; i++)
            {
                printf("{%i}[%s]\n", i, head->args[i]);
            }
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
            printf("==========================\n");
            head = head->next;
        }
        g_status = 0;
    }
    return (0);
}
