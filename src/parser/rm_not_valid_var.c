/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_not_valid_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:49:29 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/11 14:21:01 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	rm_size(char **args)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args && args[i])
	{
		if (args[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**rm_em_var2(char **args)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_args = malloc(sizeof(char *) * (rm_size(args) + 1));
	while (args && args[i])
	{
		if (args[i][0] != '\0')
			new_args[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}

void	rm_em_var(t_token *head)
{
	char	**tmp;

	while (head)
	{
		tmp = head->args;
		head->args = rm_em_var2(head->args);
		free(tmp);
		head = head->next;
	}
}
