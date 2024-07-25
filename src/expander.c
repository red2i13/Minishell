/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:56:16 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/25 11:17:12 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void ft_expand(char **cmd, t_list *envl)
{
    int i;
    char *env;
    char *tmp;
    
    i = 0;
    env = NULL;
    while(cmd[i])
    {
        if(cmd[i][0] != '$' || (cmd[i][0] == '$' && cmd[i][1] == '\0'))
        {
            i++;
            continue;
        }
        else if(cmd[i][0] == '$' && cmd[i][1] == '!')
            printf("handle this dumbass\n");
        else if(cmd[i][0] == '$' && ft_isalpha(cmd[i][1]))
        {
            tmp = cmd[i];
            env = fenv(envl, &cmd[i][1]);
            if(!env)
            {
                cmd[i] = NULL;
                return ;
            }
            cmd[i] = ft_strchr(env, '=') + 1;
            free(tmp);
        }
        i++;
    }   
}
