/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:12:48 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/24 19:37:02 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_v1(t_token **head, int *size, int *i, int *j, char *line, char *type)
{
    while (line[*j] == ' ')
        *j += 1;
    if (*size > 0)
    {
        if (*head != NULL)
        {
            if (last_t(*head)->q == 0)
                add_back_t(head, create_token(ft_substr(line, *j, *size)), 0);
        }
        else
            add_back_t(head, create_token(ft_substr(line, *j, *size)), 0);
    }
    add_back_t(head, create_token(ft_strdup(type)), 0);
    *size = 0;
    *i += 1;
    if (line[*i] == '>' || line[*i] == '<')
        *i += 1;
    while (line[*i] == ' ')
        *i += 1;
    *j = *i;
}

void init_q(t_token **head, int *size, int *i, int *j, char *line, char *type)
{
    if (*size > 0)
    {
        while (line[*j] == ' ')
            *j += 1;
        add_back_t(head, create_token(ft_substr(line, *j, *size)), 0);
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
    add_back_t(head, create_token(ft_substr(line, *j, *size)), 1);
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
        add_back_t(&head, create_token(ft_substr(line, j, size)), 0);
    }
    return head;
}

void add_t_type(t_token *head)
{
    char    *p;
    char    *f;
    char    *c;
    char    *r;
    char    *q;

    p = ft_substr("PIPE", 0, 4);
    r = ft_substr("RD", 0, 2);
    f = ft_substr("FILE", 0, 4);
    c = ft_substr("CMD", 0, 3);
    q = ft_substr("QUOTES", 0, 6);
    while (head)
    {
        if (head->value && ft_strchr(head->value, '|'))
            head->type = p;
        else if (ft_strchr(head->value, '>') || ft_strchr(head->value, '<'))
            head->type = r;
        else if (head->prev != NULL && ft_strchr(head->prev->type, 'R'))
            head->type = f;
        else if (head->q)
            head->type = q;
        else 
            head->type = c;
        head = head->next;
    }
}


char *join_tokens(t_token *head)
{
    char *join = ft_strdup("");
    while (head)
    {
        join = ft_strjoin(join, head->value);
        join = ft_strjoin(join, " ");
        head = head->next;
    }
    return  join;
}
