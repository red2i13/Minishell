/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:29:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/10 09:39:12 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_err(t_token *head)
{
	if (head->type == PIPE || last_t(head)->type == PIPE)
		return (PIPE_E);
	if (last_t(head)->type == RED || last_t(head)->type == HEREDOC)
		return (RED_E);
	while (head)
	{
		if (head->type == RED && head->arg_size > 2)
			return (RED_E);
		else if (head->type == RED && head->arg_size == 2)
		{
			if (ft_strncmp(head->args[0], head->args[1], 1))
				return (RED_E);
		}
		else if (head->next)
		{
			if (head->type == head->next->type && head->type == PIPE)
				return (PIPE_E);
			else if (RED == head->next->type && head->type == PIPE)
				return (RED_E);
			else if (PIPE == head->next->type && head->type == RED)
				return (PIPE_E);
		}
		head = head->next;
	}
	return (1);
}

void	p_err(t_err n)
{
	char	*str;

	str = "minishell: syntax error near unexpected token `>' or `<'\n";
	if (n == RED_E)
		write(2, str, ft_strlen(str));
	str = "minishell: syntax error a quote is still open\n";
	if (n == QUOTE_E)
		write(2, str, ft_strlen(str));
	str = "minishell: syntax error near unexpected token `|'\n";
	if (n == PIPE_E)
		write(2, str, ft_strlen(str));
	g_status = 2;
}
