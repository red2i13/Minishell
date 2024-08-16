/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:44:04 by codespace         #+#    #+#             */
/*   Updated: 2024/08/16 20:25:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

int get_pos(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (ft_strchr("\"\'$?", str[i]))
            return i;
        i++;
    }
    return -1;
}

char *vars_sub(char *str, int i)
{
    char *brev;
    char *var;
    char *path;
    int pos;

    pos = get_pos(&str[i]) + (ft_strchr("$?", str[i]) != 0);
    printf("%i\n", pos);
    if (pos == -1)
        pos = ft_strlen(str);
    brev = ft_substr(str, 0, i - 1);
    var = "get_p";
    if (!var && str[i] == '?')
		var = ft_itoa(g_status);
    path = ft_strjoin(brev, var);
    path = ft_strjoin(path, &str[i + pos]);
    return path;
}


char *expand(char *str)
{
    int q[2];
    int i = 0;

    q[0] = 0;
    q[1] = 0;
    while (str && str[i])
    {
        q[0] = (q[0] + (!q[1] && str[i] == '\'')) % 2;
        q[1] = (q[1] + (!q[0] && str[i] == '\"')) % 2;
        if (!q[0] && str[i] == '$' && str[i+1])
            return expand(vars_sub(str, ++i));
        i++;
    }
    return (str);
}


void start_ex(t_token *head)
{
    int i;

    i = 0;
    while (head)
    {
        i = 0;
        while (head->args[i])
        {
            head->args[i] = expand(head->args[i]);
            i++;
        }
        head = head->next;
    }
}