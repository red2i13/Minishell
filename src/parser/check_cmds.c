/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 06:30:10 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/06 16:41:20 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **cmds_trim(char *line, int *i, char **arr)
{
    int nwords;
    nwords = count_words(line, "    ", i);
    if (nwords == -1)
        printf("q err\n");
    arr = malloc(sizeof(char *) * nwords);
    if (arr == NULL)
        return (NULL);
    arr = fill_arr(arr, line, i);
    arr[nwords] = NULL;
    return arr;
}


char **check_cmds(char *line)
{
    char **arr;
    int i[3];
    if (!line)
    {
        printf("exit\n");
        return (NULL);
    }
    if(line[0] != '\0')
        add_history(line);
    i[0] = 0;
    i[1] = 0;
    arr = cmds_trim(line, i, arr);
    for (int i = 0; arr[i]; i++)
            printf("<%s>\n", arr[i]);
    i[0] = 0;
    i[1] = 0;
    int j = 0;
    int len = 0;
    char **mini;
    while (arr[j])
    {
        len = 0;
        i[0] = 0;
        i[1] = 0;
        len = count_words_2(arr[j], "<|>", i);
        mini = malloc(sizeof(char *) * len);
        mini = fill_arr_2(mini, arr[j], i, "<|>");
        arr = join_cmds(arr, mini, j);
        for (int i = 0; arr[i]; i++)
        {
            printf("[%s]\n", arr[i]);
        }
        printf("##########\n");
        j++;
    }
    return arr;
}
    
    