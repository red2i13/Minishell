/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:43:12 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/20 23:42:29 by rbenmakh         ###   ########.fr       */
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
//fix the new line opriotn
void echo(char **cmd)
{
    int i ;
    int flag;
    int flag2;
    //fixed new line 
    i = 1;
    flag = 0;
    flag2 = 0;
    while(cmd[i])
    {
        if(!flag2 && cmd[i][0] == '-' && !check_nl(&cmd[i][1]))
        {
            flag = 1;
        }
        else
        {
            if(i > 1 && flag2)
                printf(" ");
            flag2 = 1;
            printf("%s", cmd[i]);
        }
        i++;
    }
    if(!flag)
        printf("\n");
}
char*    pwd(int i)
{
    char *pwd ;
    pwd = getcwd(0, 0);
    if (i == 1)
        printf("%s\n", pwd);
    return(pwd);
}
char    *fenv(t_list    *envl, char *str)
{
    while(envl)
    {
        if(ft_strnstr((char*)envl->content, str, ft_strlen(str)))
            return(ft_strdup(envl->content));
        envl = envl->next;
    }
    return(NULL);
}

int    cd(char **args, t_list **envl, t_list **exp_list)
{
    char *path;

    path =NULL;
    if (!args[1] || args[1][0] == '~')
    {
        path = fenv(*envl, "HOME=");
        export(exp_list, envl, "OLDPWD=", pwd(0));
        chdir(path + 5);
    }
    else if(args[1][0] == '-')
    {
        path = fenv(*envl, "OLDPWD=");
        export(exp_list, envl, "OLDPWD=", pwd(0));
        chdir(path + 7);
        pwd(1);
    }
    else
    {
        export(exp_list, envl, "OLDPWD=", pwd(0));
        chdir(args[1]);
    }
    free(path);
    return(0);
}
void    print_env(t_list *envl)
{
    while(envl)
    {
        printf("%s\n", (char *)envl->content);
        envl = envl->next;
    }
}
t_list    *setup_env(char **env)
{
    t_list *envl;

    envl = NULL; 

    int i = 0;
    while(env[i])
    {
        ft_lstadd_back(&envl, ft_lstnew(ft_substr(env[i], 0, ft_strlen(env[i]))));
        i++;
    } 
    return(envl);
}
t_list  *setup_exp(t_list   *envl)
{
    t_list  *exp_list;
    char    *str;
    exp_list = NULL;
    while(envl)
    {
        str = (char*)envl->content;
        ft_lstadd_back(&exp_list, ft_lstnew(ft_substr(str, 0, ft_strlen(str))));
        envl = envl->next;
    }
    return(exp_list);
}
void print_export(t_list *exp_list)
{
    t_list  *head;
    t_list  *tmp;
    char    *temp;
    
    head = exp_list;
    while (exp_list->next)
    {
        tmp = exp_list->next;
        while(tmp)
        {
            if(ft_strncmp((char *)exp_list->content, (char *)tmp->content, ft_strlen((char *)exp_list->content)) > 0)
            {
                temp = (char *)exp_list->content;
                exp_list->content = tmp->content;
                tmp->content = temp;
            }
            tmp = tmp->next;
        }
        exp_list = exp_list->next;
    }
    while(head)
    {
        printf("%s\n", (char*)head->content);
        head = head->next;
    }
}
int find_var(t_list **list, char *var_name, char *var_value)
{
    char    *tmp;
    char    *str;
    int     flag;
    t_list *tmpl;

    flag = 0;
    tmpl = *list;
    while(tmpl)
    {
        str = (char*)tmpl->content;
        if(var_name && ft_strnstr(str, var_name, ft_strlen(var_name)))
        {
            flag = 1;
            tmp = str;
            tmpl->content = ft_strjoin(var_name, var_value);
            free(tmp);
        }
        tmpl = tmpl->next;
    }
    return(flag);
}
void export(t_list **exp_list, t_list**envl ,char *var_name, char *var_value)
{
    char    *tmp;
    char    *str;
    int     flag;
    t_list *tmpl;

    flag = 0;
    tmpl = *envl;
    while(tmpl)
    {
        str = (char*)tmpl->content;
        //debug
        printf("debug str %s\n", str);
        if(var_name && ft_strnstr(str, var_name, ft_strlen(var_name)))
        {
            flag = 1;
            tmp = str;
            tmpl->content = ft_strjoin(var_name, var_value);
            free(tmp);
        }
        tmpl = tmpl->next;
    }
    //search for export list
    t_list *tmpl2;
    int flag2;
    
    flag2 = 0;
    tmpl2 = *exp_list;
    //printf("******check %lu\n", ft_strlen(var_name) - (!ft_strchr(var_name, '=')) * 1);
    while(tmpl2)
    {
        printf("str (%s)\n", str);
        str = (char*)tmpl2->content;

        if(var_name && ft_strnstr(str, var_name,  ft_strlen(var_name)))
        {
            flag2 = 1;
            tmp = str;
            tmpl2->content = ft_strjoin(var_name, var_value);
            free(tmp);
        }
        tmpl2 = tmpl2->next;
    }
    if(!var_value && var_name)
        ft_lstadd_back(exp_list, ft_lstnew(ft_strjoin(var_name, "=")));
    if(!flag && var_name && var_value)
        ft_lstadd_back(envl, ft_lstnew(ft_strjoin(var_name, var_value)));
    if(!flag2 && var_name && var_value)
        ft_lstadd_back(exp_list, ft_lstnew(ft_strjoin(var_name, var_value)));
    if(!var_name)
        print_export(*exp_list);
    //free var_name and var_value
}

//unset command
void unset(t_list **envl, char *var_name)
{
    t_list  *env;
    t_list  *prev;
    
    env = *envl;
    prev = NULL;
    while(env)
    {
        if(ft_strncmp((char*)env->content, var_name, ft_strlen(var_name)))
        {
            if(!prev)
                (*envl) = env->next;
            else
                prev->next = env->next;
            free(env->content);
            free(env);
            break;
        }
        prev = env;
        env = env->next;
    }
}
//Add some function
char **convert_to_array(t_list *envl)
{
    int i;
    char **cenv;
    t_list *tmp;
    
    i  = 0;
    tmp = envl;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    cenv = (char **)malloc(sizeof(char *) * i + 1);
    if(!cenv)
        return(0);
    i = 0;
    while (envl)
    {
        cenv[i++] = (char *)envl->content;
        envl = envl->next;
    }
    cenv[i] = 0;
    return(cenv);
}
void    ft_exit(char *val)
{
    if (val != NULL)
        exit(ft_atoi(val) % 256);
    else
        exit(0);
}
