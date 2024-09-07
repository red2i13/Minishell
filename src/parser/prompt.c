/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:09 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/06 18:21:29 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_user(t_list  *env, int err)
{
    char *user;
    char *tmp;

    user = get_var("USER", env);
    if (!user)
        user = ft_strdup("gest");
    tmp = user;
    user = ft_strjoin("\033[0;36m", user);
    free(tmp);
    tmp = user;
    if (!err)
        user = ft_strjoin(user, "@\033[0;32mminishell →\033[0m ");
    else
        user = ft_strjoin(user, "@\033[0;32mminishell\033[0;31m →\033[0m ");
    free(tmp);
    return (user);
}

char *prompt(t_list  *env)
{
    char *user;
    char *line;

    if (!g_status)
    {
        user = get_user(env, 0);
        line = readline(user);
    }
    else
    {
        user = get_user(env, 1);
        line = readline(user);
    }
    free(user);
    return (line);
}