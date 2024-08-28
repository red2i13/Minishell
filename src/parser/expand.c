/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:44:04 by codespace         #+#    #+#             */
/*   Updated: 2024/08/28 15:30:06 by ysahraou         ###   ########.fr       */
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
        if (ft_strchr("\"\'$?#=[]!;\\*~&{}%()   ", str[i]))
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
    char *fr;
    int pos;

    pos = get_pos(&str[i]) + (ft_strchr("$?", str[i]) != 0);
    if (pos == -1)
        pos = ft_strlen(str);
    brev = ft_substr(str, 0, i - 1);
    fr = ft_substr(str, i, pos);
    var = get_var(fr, env);
    free(fr);
    if (!var && str[i] == '?')
		var = ft_itoa(g_status);
    else if (!var && str[i] == '$')
        var = ft_itoa(getpid());
    if (!var) 
        var = ft_strdup("");
    path = ft_strjoin(brev, var);
    fr = path;
    path = ft_strjoin(path, &str[i + pos]);
    free(fr);
    free(brev);
    free(var);
    free(str);
    return (path);
}


char *expand(char *str, t_list  *env, int *q, char ***temp)
{
    char *t;

    while (str && str[q[2]])
    {
        q[0] = (q[0] + (!q[1] && str[q[2]] == '\'')) % 2;
        q[1] = (q[1] + (!q[0] && str[q[2]] == '\"')) % 2;
        if (!q[0] && str[q[2]] == '$' && str[q[2]+1] && !ft_strchr("\\#=[]!;*%~&{}()   ", str[q[2]+1]) && !(ft_strchr("\"", str[q[2]+1]) && q[1]))
        {   
            q[2]++;
            if (!q[0] && !q[1] && temp)
            {
                t = vars_sub(str, q[2], env);
                *temp = ft_split(t, ' ');
                return (t);
            }
            else
            {
                return expand(vars_sub(str, q[2], env), env, q, temp);
            }
        }
        q[2]++;
    }
    if (temp)
        *temp = NULL;
    return (str);
}


void start_ex(t_token *head, t_list  *env)
{
    int i;
    int q[3];
    char ***temp;

    temp = malloc(sizeof(char **));
    i = 0;
    while (head)
    {
        i = 0;
        while (head->args[i])
        {
            *temp = NULL;
            q[0] = 0;
            q[1] = 0;
            q[2] = 0;
            head->args[i] = expand(head->args[i], env, q, temp);
            if (*temp)
            {
                
                head->args = join_cmds(head->args, *temp, i);
            }
            else
                i++;
        }
        head = head->next;
    }
    free(temp);
}
