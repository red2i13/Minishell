/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:32:57 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/12 11:23:27 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    count_words(char *line, char *set,int *i)
{
    int type_q;
    int open_q;

    type_q = 0;
    open_q = 0;
    i[0] = 0;
    i[1] = 0;
    while (line[i[0]])
    {
        if (!ft_strchr(set, line[i[0]]))
        {
            i[1]++;
            while ((!ft_strchr(set, line[i[0]]) || open_q) && line[i[0]])
            {
                if (!type_q && (line[i[0]] == '\"' || line[i[0]] == '\''))
                    type_q = line[i[0]];
                open_q = (open_q + (line[i[0]] == type_q)) % 2;
                type_q *= open_q != 0;
                i[0]++;
            }
            if (open_q)
                return (-1);
        }
        else
        {
            if (ft_strchr("<>", line[i[0]-1]))
            {
                while (ft_strchr(" \t", line[i[0]]))
                    i[0]++;
                if (ft_strchr("<>", line[i[0]]))
                    return (-2);
            }
            else
                i[0]++;
        }
        
    }
    return (i[1]);
}


char **fill_arr(char **arr, char *line, int *i)
{
    int len_line;
    int q[2];

    i[0] = 0;
    i[2] = 0;
    q[0] = 0;
    q[1] = 0;
    len_line = ft_strlen(line);
    while (line[i[0]])
    {
        while (ft_strchr("   ", line[i[0]]))
            i[0]++;
        i[1] = i[0];
        while ((!ft_strchr("   ", line[i[0]]) || q[1] || q[0]) && line[i[0]])
        {
            q[0] = (q[0] + (!q[1] && line[i[0]] == '\'')) % 2;
            q[1] = (q[1] + (!q[0] && line[i[0]] == '\"')) % 2;
            i[0]++;
        }
        if (i[1] >= len_line)
            arr[i[2]++] = ft_strdup("\0");
        else
            arr[i[2]++] = ft_substr(line, i[1], i[0] - i[1]);
    }
    return (arr[i[2]] = NULL, arr);
}

    