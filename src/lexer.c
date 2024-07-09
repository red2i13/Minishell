/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:12:48 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/09 14:25:52 by ysahraou         ###   ########.fr       */
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
void    init_redirec(t_token **t,char *str, char *op)
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
        
        add_back_t(t, create_token(tokens[i]));
        if (count)
        {
            add_back_t(t, create_token(sign));
            count--;
        }
        i++;
    }
}

t_token *init_tokens(char *line)
{
    int i = 0;
    int size = 0;
    int j = i;
    t_token *head = NULL;
    while (line[i])
    {
        if (line[i] == '|')
        {
            add_back_t(&head, create_token(ft_substr(line, j, size)));
            add_back_t(&head, create_token(ft_strdup("|")));
            size = 0;
            i++;
            j = i;
        }
        else if (line[i] == '>' && line[i+1] == '>')
        {
            add_back_t(&head, create_token(ft_substr(line, j, size)));
            add_back_t(&head, create_token(ft_strdup(">>")));
            size = 0;
            i++;
            i++;
            j = i;
        }
        else if (line[i] == '<' && line[i+1] == '<')
        {
            add_back_t(&head, create_token(ft_substr(line, j, size)));
            add_back_t(&head, create_token(ft_strdup("<<")));
            size = 0;
            i++;
            i++;
            j = i;
        }
        else if (line[i] == '>')
        {
            add_back_t(&head, create_token(ft_substr(line, j, size)));
            add_back_t(&head, create_token(ft_strdup(">")));
            size = 0;
            i++;
            j = i;
        }
        else if (line[i] == '<')
        {
            add_back_t(&head, create_token(ft_substr(line, j, size)));
            add_back_t(&head, create_token(ft_strdup("<")));
            size = 0;
            i++;
            j = i;
        }
        size++;
        i++;
    }
    add_back_t(&head, create_token(ft_substr(line, j, size)));
    return head;
}

void add_t_type(t_token *head)
{
    char    *p;
    char    *f;
    char    *c;
    char    *r;

    p = ft_substr("PIPE", 0, 4);
    r = ft_substr("RD", 0, 2);
    f = ft_substr("FILE", 0, 4);
    c = ft_substr("CMD", 0, 3);
    while (head)
    {
        if (head->value && ft_strchr(head->value, '|'))
            head->type = p;
        else if (ft_strchr(head->value, '>') || ft_strchr(head->value, '<'))
            head->type = r;
        else if (head->prev != NULL && ft_strchr(head->prev->type, 'R'))
            head->type = f;
        else 
            head->type = c;
        head = head->next;
    }
}
