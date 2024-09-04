/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions_v2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:40:34 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/04 12:57:32 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_front_t(t_token **lst, t_token *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	(*lst)->prev = new;
	*(lst) = new;
}
