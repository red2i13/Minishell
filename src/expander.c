/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:56:16 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/24 21:33:16 by rbenmakh         ###   ########.fr       */
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
            continue;
        else if(cmd[i][0] == '$' && cmd[i][1] == '!')
            printf("handle this dumbass\n");
        else if(cmd[i][0] == '$' && ft_isalpha(cmd[i][1]))
        {
            env = fenv(envl, &cmd[i][1]);
            tmp = cmd[i];
            cmd[i] = env;
            free(tmp);
        }
        i++;
    }   
}