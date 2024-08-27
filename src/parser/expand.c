/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:44:04 by codespace         #+#    #+#             */
/*   Updated: 2024/08/27 10:19:40 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

int	ft_ncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if ((i == n || (s1[i] == '\0' && s2[i] == '\0')) && s2[i] == '=')
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *get_var(char *str, t_list  *env)
{
    if (str && str[0] == '\0')
        return NULL;
    while (env)
    {
        if (ft_ncmp(str, env->content, ft_strlen(str)) == 0)
        {
            return ft_substr(env->content, ft_strlen(str)+1, ft_strlen(env->content));
        }
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
        if (ft_strchr("\"\'$?=", str[i]))
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
    if (pos == -1)
        pos = ft_strlen(str);
    brev = ft_substr(str, 0, i - 1);
    var = get_var(ft_substr(str, i, pos), env);
    if (!var && str[i] == '?')
		var = ft_itoa(g_status);
    if (!var) 
        var = ft_strdup("");
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
        if (!q[0] && str[i] == '$' && str[i+1] && !ft_strchr("=:", str[i+1]))
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