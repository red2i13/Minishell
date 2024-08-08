/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/07 20:08:38 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{ 
    char    *line;
    char **args;

    (void)argc;
    (void)argv;
    (void)env;
    while (1)
    {
        line = readline("Minishell$ ");
        args = check_cmds(line);
        init_tokens(args);
        for (int i = 0; args[i]; i++)
            printf("[%s]\n", args[i]);
    }
    return (0);
}
