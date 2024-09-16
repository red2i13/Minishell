/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:49:01 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/16 12:01:50 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input_redirection(char *filename)
{
	if (access(filename, F_OK))
		return (1);
	else if (!access(filename, F_OK) && access(filename, F_OK | R_OK) == -1)
	{
		return (1);
	}
	return (0);
}

int	check_while_input_redirection(t_token *list)
{
	char	*filename;

	while (list)
	{
		filename = list->args[0];
		if (!filename || !filename[0])
		{
			list = list->next;
			continue ;
		}
		if (access(filename, F_OK))
			return (1);
		else if (!access(filename, F_OK) && access(filename, F_OK | R_OK) == -1)
		{
			return (1);
		}
		list = list->next;
	}
	return (0);
}
