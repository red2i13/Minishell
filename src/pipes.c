/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:50:47 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/31 20:55:07 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int calc_pipes(t_token *list)
{
    int p;

    p = 0;
    while (list)
    {
        if(list->value[0] == '|')
            p++;
        list = list->next; 
    }
    return(p);
}
int init_pipes(int p)
{
    int *fdt;
    
    fdt = (int*)malloc(sizeof(int) * p);
    while(p)
    {
        pipe
    }
    
}