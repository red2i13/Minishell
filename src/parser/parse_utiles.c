/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:48:51 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/10 11:17:52 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_rm(t_token **head, t_list *envl)
{
	start_ex(*head, envl);
	rm_em_var(*head);
	start_rm_q(*head);
	while (1)
		if (cmd_mk(*head))
			break ;
	cmd_mk_v2(head);
	set_type(*head);
	set_size(*head);
}
