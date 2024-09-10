/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:53:02 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/10 09:59:27 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	calc_pipes(t_token *list)
{
	int	p;

	p = 0;
	while (list)
	{
		if (list->args[0] && list->args[0][0] == '|')
			p++;
		list = list->next;
	}
	return (p);
}

char	**convert_to_array(t_list *envl)
{
	int		i;
	char	**cenv;
	t_list	*tmp;

	i = 0;
	tmp = envl;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	cenv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cenv)
		return (0);
	i = 0;
	while (envl)
	{
		cenv[i++] = (char *)envl->content;
		envl = envl->next;
	}
	cenv[i] = 0;
	return (cenv);
}
