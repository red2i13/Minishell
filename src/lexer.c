/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:12:48 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/12 10:40:24 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_v1(t_token **head, int *size, int *i, int *j, char *line, char *type)
{
    while (line[*j] == ' ')
        *j += 1;
    if (*size > 0)
        add_back_t(head, create_token(ft_substr(line, *j, *size)));
    add_back_t(head, create_token(ft_strdup(type)));
    *size = 1;
    *i += 1;
    if (line[*i] == '>' || line[*i] == '<')
        *i += 1;
    *j = *i;
}

void init_q(t_token **head, int *size, int *i, int *j, char *line, char *type)
{
    if (*size > 0)
    {
        while (line[*j] == ' ')
            *j += 1;
        add_back_t(head, create_token(ft_substr(line, *j, *size)));
        *size = 0;
        *i += 1;
        *j = *i;
    }
    else
    {
        *i += 1;
        *j = *i;
    }
    while (line[*i] != *type)
    {
        *size += 1;
        *i += 1;
    }
    add_back_t(head, create_token(ft_substr(line, *j, *size)));
    *size = 0;
    *i += 1;
    *j = *i;
}


void init_v2(t_token **head, int *size, int *i, int *j, char *line)
{
    if (line[*i] == '"')
        init_q(head, size, i, j, line, "\"");
    else if (line[*i] == '\'')
        init_q(head, size, i, j, line, "'");
    else if (line[*i] == '|')
        init_v1(head, size, i, j, line, "|");
    else if (line[*i] == '>' && line[*i+1] == '>')
        init_v1(head, size, i, j, line, ">>");
    else if (line[*i] == '<' && line[*i+1] == '<')
        init_v1(head, size, i, j, line, "<<");
    else if (line[*i] == '>')
        init_v1(head, size, i, j, line, ">");
    else if (line[*i] == '<')
        init_v1(head, size, i, j, line, "<");
    else 
    {
        if (line[*i] != ' ')
            *size += 1;
        *i += 1;
    }
}

t_token *init_tokens(char *line)
{
    int i = 0;
    int size = 0;
    int j = i;
    t_token *head = NULL;
    while (line[i])
        init_v2(&head, &size, &i, &j, line);
    if (size > 0)
    {
        while (line[j] == ' ')
            j++;
        add_back_t(&head, create_token(ft_substr(line, j, size)));
    }
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
