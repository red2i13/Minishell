/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:04:22 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/10 11:26:28 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_back_t(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!head || !*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_token	*last_t(t_token *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_token	*create_token(char **args)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->args = args;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

size_t	size_list(t_token *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	list_clear(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free_arr((*head)->args);
		(*head)->args = NULL;
		free((*head));
		(*head) = tmp;
	}
	*head = NULL;
}
