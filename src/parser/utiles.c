/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:16:11 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/04 10:21:48 by ysahraou         ###   ########.fr       */
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

int cmd_mk(t_token *head)
{
    int i;
    char **file;
    
    set_index(head);
    set_size(head);
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
            return (0); 
        }
        head = head->next;
    }
    return (1);
}

void del(void *c)
{
    free(c);
}

void cmd_mk_v2(t_token **head)
{
    int i;
    char **file;
    char **args;
    
    args = NULL;
    if (size_list(*head) >= 2)
    {
        if ((*head)->next->type == FILE_N && (*head)->next->arg_size >= 2)
        {
            i = 1;
            file = malloc(sizeof(char *) * 2);
            file[0] = (*head)->next->args[0];
            file[1] = NULL;
            while ((*head)->next->args[i])
            {
                args = ft_realloc((*head)->next->args[i], args);
                i++;
            }
            free((*head)->next->args);
            (*head)->next->args = file;
            add_front_t(head, create_token(args));
        }
    }
    set_index(*head);
    set_size(*head);
}
