/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:43:12 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/08 11:34:48 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_nl(char *s)
{
    while(*s)
    {
        if(*s != 'n')
            return(1);
        s++;
    }
    return(0);
}
void echo(char **cmd)
{
    int i ;
    int flag;
    int flag2;
    i = 1;
    flag = 0;
    flag2 = 0;
    while(cmd[i])
    {
        if(cmd[i][0] == '-' && !check_nl(&cmd[i][1]) && !flag2)
        {
            flag = 1;
        }
        else
        {
            flag2 = 1;
            printf("%s", cmd[i]);
        }
        i++;
    }
    if(!flag)
        printf("\n");
}

int    cd(char **args)
{
    if(chdir(args[1]) != 0)
        //write and exit on error
        return(1);
    return(0);
    
}
void    pwd(char **args)
{
    char *path ;
    (void)args;
    path = getcwd(0, 0);

    printf("%s\n", path);
}
void print_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}
void export(char **env, char *var_name, char *var_value)
{
    (void)var_name;
    (void)var_name;

    int i;
    int j;

    i = 0;
    while(env[i])
    {
        j = i + 1;
        while(env[j])
        {
            
            j++;
        }
        i++;
    }
}

