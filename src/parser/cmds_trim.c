/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:32:57 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/31 12:58:34 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int process_quotes(char *line, char *set, int *i, int *q)
{
    while ((!ft_strchr(set, line[i[0]]) || q[0]) && line[i[0]])
    {
        if (!(q[1]) && (line[i[0]] == '\"' || line[i[0]] == '\''))
            q[1] = line[i[0]];
        q[0] = (q[0] + (line[i[0]] == q[1])) % 2;
        q[1] *= q[0] != 0;
        i[0]++;
    }
    if (q[0])
        return (-1);
    return 0;
}
void set_a(int *i, int *q)
{
    q[0] = 0;
    q[1] = 0;
    i[0] = 0;
    i[1] = 0;
}
int count_words(char *line, char *set, int *i)
{
    int q[2];

    set_a(i, q);
    while (line[i[0]])
    {
        if (!ft_strchr(set, line[i[0]]))
        {
            i[1]++;
            if (process_quotes(line, set, i, q) == -1)
                return (-1);
        }
        else
        {
            if (i[0] > 1 && ft_strchr("<>", line[i[0]-1]))
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
        while (ft_strchr(" \t", line[i[0]]) && line[i[0]])
            i[0]++;
        i[1] = i[0];
        while ((!ft_strchr(" \t", line[i[0]]) || q[1] || q[0]) && line[i[0]])
        {
            q[0] = (q[0] + (!q[1] && line[i[0]] == '\'')) % 2;
            q[1] = (q[1] + (!q[0] && line[i[0]] == '\"')) % 2;
            i[0]++;
        }
        if (i[1] < len_line)
            arr[i[2]++] = ft_substr(line, i[1], i[0] - i[1]);
    }
    return (arr);
}

    