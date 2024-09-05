/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:09:35 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/04 11:38:35 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fun_init(char ***new_args, t_token **head, char **args, int *i)
{
	if (*new_args)
		add_back_t(head, create_token(*new_args));
	*new_args = NULL;
	while (args[*i] && ft_strchr("<>", args[*i][0]))
	{
		*new_args = ft_realloc(args[*i], *new_args);
		*i += 1;
	}
	add_back_t(head, create_token(*new_args));
	*new_args = NULL;
}

void	fun_init_v2(char ***new_args, t_token **head, char **args, int *i)
{
	if (*new_args)
		add_back_t(head, create_token(*new_args));
	*new_args = malloc(sizeof(char *) * 2);
	*new_args[0] = args[*i];
	*new_args[1] = NULL;
	add_back_t(head, create_token(*new_args));
	*new_args = NULL;
	*i += 1;
}
