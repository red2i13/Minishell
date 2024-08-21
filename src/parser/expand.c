/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:44:04 by codespace         #+#    #+#             */
/*   Updated: 2024/08/21 12:17:20 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

char *get_var(char *str, t_list  *env)
{
    // printf("%s\n", str);
    while (env)
    {
        if (ft_strncmp(str, env->content, ft_strlen(str)) == 0)
            return ft_substr(env->content, ft_strlen(str)+1, ft_strlen(env->content));
        env = env->next;
    }
    return NULL;
}

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

char *vars_sub(char *str, int i, t_list  *env)
{
    char *brev;
    char *var;
    char *path;
    int pos;

    pos = get_pos(&str[i]) + (ft_strchr("$?", str[i]) != 0);
    //printf("%i\n", pos);
    if (pos == -1)
        pos = ft_strlen(str);
    brev = ft_substr(str, 0, i - 1);
    var = get_var(ft_substr(str, i, pos), env);
    if (!var && str[i] == '?')
		var = ft_itoa(g_status);
    path = ft_strjoin(brev, var);
    path = ft_strjoin(path, &str[i + pos]);
    return path;
}


char *expand(char *str, t_list  *env)
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
            return expand(vars_sub(str, ++i, env), env);
        i++;
    }
    return (str);
}


void start_ex(t_token *head, t_list  *env)
{
    int i;

    i = 0;
    while (head)
    {
        i = 0;
        while (head->args[i])
        {
            head->args[i] = expand(head->args[i], env);
            i++;
        }
        head = head->next;
    }
}