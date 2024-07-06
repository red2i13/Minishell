/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:43:12 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/05 23:22:09 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_nl(char *s)
{
    while(*s)
    {
        if(*s != 'n')
            return(1);
        s++;
    }
    return(0);
}
void echo(char **cmd)
{
    int i ;
    int flag;
    int flag2;
    i = 1;
    flag = 0;
    flag2 = 0;
    while(cmd[i])
    {
        if(cmd[i][0] == '-' && !check_nl(&cmd[i][1]) && !flag2)
        {
            flag = 1;
        }
        else
        {
            flag2 = 1;
            printf("%s", cmd[i]);
        }
        i++;
    }
    if(!flag)
        printf("\n");
}


