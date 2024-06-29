/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/28 18:55:05 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
    char    *line;
    char    **args;
    char    **paths;

    (void)argc;
    (void)argv;
    
    paths = get_paths(env);
    // while (*paths)
    //     printf("%s\n", *paths++);
    while (1)
    {
        line = readline("Minishell$");
        args = ft_split(line, ' ');
        // print the args
        for (int i = 0; args[i]; i++)
            printf("%s\n", args[i]);
        printf("%s\n", check_cmd("ls", paths));
        add_history(line);
    }
    return (0);
}