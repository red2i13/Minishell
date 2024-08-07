/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 06:30:18 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/05 15:32:12 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *line;
    while (1)
    {
        line = readline("Minishell$");
        char **arr = check_cmds(line);
        if (!arr)
            return (0);
    }
    return (0);
}