/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:12:48 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/03 13:13:41 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_op(char *cmd, char *op)
{
    int count;
    int i;
    char **scmd = ft_split(cmd, ' ');

    count = 0;
    i = 0;
    while(scmd[i])
    {
        if(ft_strnstr(scmd[i], op, ft_strlen(scmd[i])))
            count++;
        i++;
    }
    return(count);
}
void    init_redirec(t_token *t,char *str, char *op)
{
    char **tokens;
    int i;
    int count; 
    
    i = 0;
    tokens = ft_split(str, op[0]);
    count = count_op(str, op);
    char *sign = ft_substr(op, 0, 2);
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
    
    count = count_op(cmd, "|");    
    list = NULL;
    i = 0;
    tokens = ft_split(cmd, '|');
    while(tokens[i])
    {
        if  (ft_strnstr(tokens[i], ">>", ft_strlen(tokens[i])))
            init_redirec(list, tokens[i], ">>");
        else if  (ft_strnstr(tokens[i], "<<", ft_strlen(tokens[i])))
            init_redirec(list, tokens[i], "<<");
        else if  (ft_strchr(tokens[i], '<'))
            init_redirec(list, tokens[i],"<");
        else if  (ft_strchr(tokens[i], '>'))
            init_redirec(list, tokens[i],">");
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

void add_t_type(t_token *head)
{
    while (head)
    {
        if (ft_strchr(head->value, '|'))
            head->type = ft_substr("PIPE", 0, 4);
        else if (ft_strchr(head->value, '>') || ft_strchr(head->value, '<'))
            head->type = ft_substr("RD", 0, 2);
        else if (head->prev != NULL && ft_strchr(head->prev->type, 'R'))
            head->type = ft_substr("FILE", 0, 4);
        else 
            head->type = ft_substr("CMD", 0, 3);
        head = head->next;
    }
}
