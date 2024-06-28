/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/28 18:10:53 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
    char    *line;
    char    **args;

    while (1)
    {
        line = readline("Minishell$");
        args = ft_split(line, ' ');
        // print the args
        for (int i = 0; args[i]; i++)
            printf("%s\n", args[i]);
        add_history(line);
    }
    return (0);
}