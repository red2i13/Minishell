/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/29 12:14:51 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
    char    *line;
    char    **args;
    char    **paths;
    int pid;

    (void)argc;
    (void)argv;
    
    paths = get_paths(env);
    // while (*paths)
    //     printf("%s\n", *paths++);
    while (1)
    {
        line = readline("Minishell$");
        if (line[0] == '\0')
            continue;
        args = ft_split(line, ' ');
        // print the args
        for (int i = 0; args[i]; i++)
            printf("%s\n", args[i]);
        pid = fork();
        if (pid == 0)
        {
            char *path = check_cmd(args[0], paths);
            printf("%s\n", path);
            execve(path, args, env);
            exit(0);
        }
        wait(0);
        add_history(line);
    }
    return (0);
}