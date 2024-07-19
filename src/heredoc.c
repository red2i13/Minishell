/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesssahraoui <younesssahraoui@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:50:20 by younesssahr       #+#    #+#             */
/*   Updated: 2024/07/19 17:40:55 by younesssahr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char  *heredoc(char *end)
{
    char *str;
    char *line;

    str = ft_calloc(1, 1);
    while (1)
    {
        write(1, ">", 1);
        line = get_next_line(0);
        if (ft_strnstr(line, end, ft_strlen(end)) != 0)
            break;
        str = ft_strjoin(str, line);
    }
    return str;
}

int main()
{
    char *str = heredoc("end");
    printf("%s", str);
}