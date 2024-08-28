/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 08:10:13 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/28 15:03:42 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_cmd(char **arr)
{
    int count;

    count = 0;
    while (arr && arr[count])
        count++;
    return (count);
}
char **join_cmds(char **big, char **mini, int pos)
{
    int bc;
    int mc;
    char **ret_arr;
    int i[3];

    bc = count_cmd(big);
    mc = count_cmd(mini);
    ret_arr = malloc(sizeof(char *) * (bc + mc));
    i[0] = 0;
    i[2] = 0;
    while (big[i[0]])
    {
        if (i[0] != pos)
            ret_arr[i[2]++] = big[i[0]];
        else
        {
            i[1] = 0;
            while (mini && mini[i[1]])
                ret_arr[i[2]++] = mini[i[1]++];
            free(big[i[0]]);
        }
        i[0]++;
    }
    ret_arr[i[2]] = NULL;
    free(big);
    free(mini);
    return ret_arr;
}
