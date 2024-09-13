/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:48:51 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/13 15:45:54 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_rm(t_token **head, t_list *envl)
{
	int		q[4];
	char	***temp;

	temp = malloc(sizeof(char **));
	start_ex(*head, envl, q, temp);
	rm_em_var(*head);
	start_rm_q(*head);
	while (1)
		if (cmd_mk(*head))
			break ;
	while (1)
		if (cmd_mk_2(*head))
			break ;
	cmd_mk_v2(head);
	set_type(*head);
	set_size(*head);
}
