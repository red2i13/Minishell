/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:12:48 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/02 14:29:08 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_pipa(char *cmd)
{
    int count;

    count = 0;
    while(*cmd)
    {
        if(*cmd == '|')
            count++;
        cmd++;
    }
    return(count);
}
t_token *init_tokens(char *cmd)
{
    int i;
    int count ;
    char **tokens;
    t_token *list;
    
    count = count_pipa(cmd);    
    list = NULL;
    i = 0;
    tokens = ft_split(cmd, '|');
    while(tokens[i])
    {
        add_back_t(&list, create_token(tokens[i++]));
        if (count)
        {
            add_back_t(&list, create_token("|"));
            count--;
        }
    }
    t_token *tmp;
    while(list)
    {
        if(ft_strchr(list->value, '>') || ft_strchr(list->value, '<'))
        {
            // remove a node and replace it with two nodes
        }
        list = list->next ;
    }
    return (list);
}