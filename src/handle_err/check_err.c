/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:29:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/11 11:01:08 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

int check_err(t_token *head)
{
    if (head->type == PIPE || last_t(head)->type == PIPE)
        return (-3);
    if (last_t(head)->type == RED || last_t(head)->type == HEREDOC)
        return (-2);
    while (head)
    {
        if (head->type == RED && head->arg_size > 2)
            return (-2);
        else if (head->type == RED && head->arg_size == 2)
        {
            if (ft_strncmp(head->args[0], head->args[1], 1))
                return (-2);
        }
        else if (head->next)
        {
            if (head->type == head->next->type && head->type == PIPE)
                return (-3);
        }
        head = head->next;
    }
    return (1);
}

void p_err(t_err n)
{
    if (n == RED_E)
        printf("minishell: syntax error near unexpected token `>' or `<'\n");
    if (n == QUOTE_E)
        printf("minishell: syntax error a quote is still open\n");
    if (n == PIPE_E)
        printf("minishell: syntax error near unexpected token `|'\n");
    g_status = 2;
}
