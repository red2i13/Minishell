/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:29:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/09 16:07:44 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_err(t_token *head)
{
    while (head)
    {
        if (head->type == RED && head->arg_size > 2)
            return (-1);
        else if (head->type == RED && head->arg_size == 2)
            if (ft_strncmp(head->args[0], head->args[1], 1))
                return (-1);
        head = head->next;
    }
    return (1);
}