/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:40:47 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/31 15:12:20 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *cmds_parse(char *line)
{
    char **args;
    t_token *head;

    args = get_cmds(line);
    if (!args)
        return NULL;
    head = init_tokens(args);
    if (!head)
        return (NULL);
    set_size(head);
    set_type(head);
    if (check_err(head) < 0)
    {
        p_err(check_err(head));
        list_clear(head);
        head = NULL;
    }
    return (head);
}
