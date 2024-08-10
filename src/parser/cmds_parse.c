/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:40:47 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/10 16:05:53 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_t(t_token *head)
{
    t_token *tmp;
    
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}


t_token *cmds_parse(char *line)
{
    char **args;
    t_token *head;

    args = get_cmds(line);
    if (!args)
        return NULL;
    head = init_tokens(args);
    if (!head)
        printf("stfu\n");
    set_size(head);
    set_type(head);
    if (check_err(head) < 0)
    {
        p_err(check_err(head));
        free_t(head);
        head = NULL;
    }
    return (head);
}
