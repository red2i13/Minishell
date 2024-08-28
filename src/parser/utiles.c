/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:16:11 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/28 16:34:54 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
    arr = NULL;
}
void set_index(t_token *head)
{
    int i;

    i = 0;
    while (head)
    {
        head->index = i++;
        head = head->next;
    }
}

void cmd_mk(t_token *head)
{
    set_index(head);
    int i;
    char **file;
    
    while (head)
    {
        if (head->type == FILE_N && head->index >= 2 && head->arg_size >= 2)
        {
            i = 1;
            file = malloc(sizeof(char *) * 2);
            file[0] = head->args[0];
            file[1] = NULL;
            while (head->args[i])
            {
                head->prev->prev->args = ft_realloc(head->args[i], head->prev->prev->args);
                i++;
            }
            head->args = file;   
        }
        head = head->next;
    }
}

void del(void *c)
{
    free(c);
}