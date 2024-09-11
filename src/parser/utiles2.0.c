/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:33:45 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/11 14:24:24 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_rep_token(t_token *prev, t_token *new, t_token *next)
{
	prev->next = new;
	new->prev = prev;
	new->next = next;
	next->prev = new;
}

int	cmd_mk_2(t_token *head)
{
	int		i;
	char	**pipe;
	char	**new_args;

	set_index(head);
	set_size(head);
	while (head)
	{
		new_args = NULL;
		if (head->type == PIPE && head->index >= 1 && head->arg_size >= 2)
		{
			i = 0;
			pipe = malloc(sizeof(char *) * 2);
			pipe[0] = head->args[0];
			pipe[1] = NULL;
			while (head->args[++i])
				new_args = ft_realloc(head->args[i], new_args);
			free(head->args);
			head->args = pipe;
			ft_rep_token(head, create_token(new_args), head->next);
			return (0);
		}
		head = head->next;
	}
	return (1);
}
