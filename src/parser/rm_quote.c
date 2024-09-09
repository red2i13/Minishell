/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:04:01 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/07 13:08:05 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ff_realloc(char *old, char c)
{
	char	*new;
	int		i;

	if (!old)
		old = ft_calloc(sizeof(char), 1);
	new = ft_calloc(sizeof(char), ft_strlen(old) + 2);
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = c;
	free(old);
	return (new);
}

void	rm_quote_1(char **new, int *q, char *str, int *i)
{
	if (q[1] && str[*i] == '\"')
	{
		while (q[1] && str[*i])
		{
			*i += 1;
			q[1] = (q[1] + (!q[0] && str[*i] == '\"')) % 2;
			if (q[1] && str[*i])
				*new = ff_realloc(*new, str[*i]);
		}
		*i += 1;
	}
	else if (q[0] && str[*i] == '\'')
	{
		while (q[0] && str[*i])
		{
			*i += 1;
			q[0] = (q[0] + (!q[1] && str[*i] == '\'')) % 2;
			if (q[0] && str[*i])
				*new = ff_realloc(*new, str[*i]);
		}
		*i += 1;
	}
	else
		*new = ff_realloc(*new, str[(*i)++]);
}

char	*rm_quote(char *str)
{
	int		i;
	char	*new;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	i = 0;
	new = NULL;
	while (str[i])
	{
		q[0] = (q[0] + (!q[1]) && str[i] == '\'') % 2;
		q[1] = (q[1] + (!q[0]) && str[i] == '\"') % 2;
		rm_quote_1(&new, q, str, &i);
	}
	if (!new)
		new = ft_strdup("");
	free(str);
	return (new);
}

void	start_rm_q(t_token *head)
{
	int	i;

	while (head)
	{
		i = 0;
		while (head->args[i])
		{
			if (is_q(head->args[i]))
				head->args[i] = rm_quote(head->args[i]);
			i++;
		}
		head = head->next;
	}
}
