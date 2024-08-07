/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_trim_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:32:57 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/06 07:56:15 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_words_2(char *line, char *set,int *i)
{
    int q[2];

    i[0] = 0;
    i[2] = 0;
    q[0] = 0;
    q[1] = 0;
    while (line[i[0]])
    {
        i[1]++;
        if (!ft_strchr(set, line[i[0]]))
        {
            while ((!ft_strchr(set, line[i[0]]) || q[1] || q[0]) && line[i[0]])
            {
                q[0] = (q[0] + (!q[1] && line[i[0]] == '\'')) % 2;
                q[1] = (q[1] + (!q[0] && line[i[0]] == '\"')) % 2;
                i[0]++;
            }
        }
        else 
            i[0]++;
        
    }
    return (i[1]);
}


char **fill_arr_2(char **arr, char *line, int *i, char *set)
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
        i[1] = i[0];
        if (!ft_strchr(set, line[i[0]]))
        {
            while ((!ft_strchr(set, line[i[0]]) || q[1] || q[0]) && line[i[0]])
            {
                q[0] = (q[0] + (!q[1] && line[i[0]] == '\'')) % 2;
                q[1] = (q[1] + (!q[0] && line[i[0]] == '\"')) % 2;
                i[0]++;
            }
        }
        else
            i[0]++;
        arr[i[2]++] = ft_substr(line, i[1], i[0] - i[1]);
    }
    return (arr[i[2]] = NULL, arr);
}

    