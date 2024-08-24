/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 06:30:10 by ysahraou          #+#    #+#             */

/*   Updated: 2024/08/10 12:39:58 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **cmds_trim(char *line, int *i, char **arr)
{
    int nwords;
    i[0] = 0;
    i[1] = 0;
    nwords = count_words(line, "     ", i);
    if (nwords < 0)
        return (p_err(nwords), NULL);
    arr = malloc(sizeof(char *) * (nwords+1));
    if (arr == NULL)
        return (NULL);
    arr = fill_arr(arr, line, i);
    arr[nwords] = NULL;
    return arr;
}


char **get_cmds(char *line)
{
    char **arr;
    int i[3];

    arr = NULL;
    add_history(line);
    arr = cmds_trim(line, i, arr);
    int j = 0;
    int len = 0;
    char **mini;
    while (arr && arr[j])
    {
        len = 0;
        len = count_words_2(arr[j], "<|>", i);
        mini = malloc(sizeof(char *) * (len+1));
        mini = fill_arr_2(mini, arr[j], i, "<|>");
        arr = join_cmds(arr, mini, j);
        j++;
    }
    return arr;
}
    
    
    