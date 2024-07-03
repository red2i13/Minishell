/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:12:48 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/03 10:16:27 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_op(char *cmd, char op)
{
    int count;

    count = 0;
    while(*cmd)
    {
        if(*cmd == op)
            count++;
        cmd++;
    }
    return(count);
}
void    init_redirec(t_token *t,char *str, char op)
{
    char **tokens;
    int i;
    int count; 
    
    i = 0;
    tokens = ft_split(str, op);
    count = count_op(str, op);
    char *sign = ft_substr(&op, 0, 1);
    while(tokens[i])
    {
        
        add_back_t(&t, create_token(tokens[i]));
        if (count)
        {
            add_back_t(&t, create_token(sign));
            count--;
        }
        i++;
    }
}
t_token *init_tokens(char *cmd)
{
    int i;
    int count ;
    char **tokens;
    t_token *list;
    
    count = count_op(cmd, '|');    
    list = NULL;
    i = 0;
    tokens = ft_split(cmd, '|');
    while(tokens[i])
    {
        if  (ft_strchr(tokens[i], '<'))
            init_redirec(list, tokens[i], '<');
        else if  (ft_strchr(tokens[i], '>'))
            init_redirec(list, tokens[i], '>');
        else
            add_back_t(&list, create_token(tokens[i]));
        if (count)
        {
            add_back_t(&list, create_token("|"));
            count--;
        }
        i++;
    }
    return (list);
}
