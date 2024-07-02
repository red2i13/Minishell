/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/02 11:46:47 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
    char    *line;
    char    **paths;

    (void)argc;
    (void)argv;
    
    paths = split_paths(get_PATH(env));
    // while (*paths)
    //     printf("%s\n", *paths++);
    while (1)
    {
        line = readline("Minishell$");
        if (line[0] == '\0')
            continue;
        // print the args
        t_token *head = init_tokens(line);
        while (head)
        {
            printf("%s\n", head->value);
            head = head->next;
        }
        
        add_history(line);
    }
    return (0);
}