/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/23 19:12:26 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
//fix the command if is it in the path
void run_cmd(t_token *head, t_list **envl, t_list **exp_list ,char **paths)
{
    int pid;
    char *cmd;
    char **env ;
    (void)pid;
    
    env= convert_to_array(*envl);
    //make exit function with 2n states run in child and in the main process
    cmd = check_cmd(head->args[0], paths);
    // if(!cmd)
    //     return;
    if (ft_strnstr(head->value, "exit", ft_strlen("exit")))
            ft_exit(head->args[1]);
    if(ft_strnstr(head->args[0], "cd", 3))
        cd(head->args, envl, exp_list);
    else if(ft_strnstr(head->args[0], "echo", 5))
        echo(head->args);
    else if(ft_strnstr(head->args[0], "export", 7))
    {
        char *f ;
        f = NULL;
        if(head->args[1])
            f= ft_strchr(head->args[1], '=');
        char *var_value;
        char *var_name;
        
        var_name = NULL;
        var_value = NULL;
        if(!f && head->args[1])
        {
            var_name = ft_substr(head->args[1], 0, ft_strlen(head->args[1]));
            //var_value = ft_strdup("");
        }
        else if(f && head->args[1])
        {
            var_name =  ft_substr(head->args[1], 0, f - head->args[1] + 1 );
            var_value = ft_strdup(ft_strchr(head->args[1], '=') + 1);
        }
        export(exp_list,envl,var_name, var_value);
    }
    else if(ft_strnstr(head->args[0], "unset", 6))
    {
        unset(envl, head->args[1]);
        unset(exp_list, head->args[1]); 
    }
    else if(ft_strnstr(head->args[0], "env", 4))
        print_env(*envl);
    else
    {
        pid = fork();
        if(!pid)
        {
            if(execve(cmd, head->args, env) == -1)
            {
                //use perror of strerror function
                //perror("Error ");
                // char *error = strerror(errno);
                // printf("debug %s\n", error);
                exit(127);
            }
        }
        else
            wait(0);  
    }
}

void p_cmd(t_token *head)
{
    int i = 0;
    while (head)
    {
        printf("#########################\n");
        printf("%i: Token => %s\n", i, head->value);
        if (head->args != NULL)
        {
            for (int i = 0; head->args[i]; i++)
            {
                printf("arg[%i] => (%s)\n", i, head->args[i]);
            }
        }
        else
            printf("args => (%s)\n", "NULL");
        printf("Type => %s\n", head->type);
        i++;
        head = head->next;
    }
}
//funcitons for signals
void sighandler(int signum) 
{
    if(signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void signal_setup()
{
    signal(SIGINT, sighandler);
    signal(SIGQUIT, SIG_IGN);
    //signal(EOF, sighandler);
}
//
int main(int argc, char **argv, char **env)
{ 
    char    *line;
    //char    **paths;
    t_list  *envl ;
    t_list  *exp_list;

    (void)argc;
    (void)argv;
    //(void)paths;
    signal_setup();
    envl= setup_env(env);
    //paths = split_paths(get_PATH(envl));
    exp_list = setup_exp(envl);
    while (1)
    {
        line = readline("Minishell$ ");
        //uncomment when finish debugging
        // pid = fork();
        // if (!pid)
        // {
        //     check_syntax(line);
        //     exit(0);
        // }
        // else
        //     wait(0);
        //printf("%i\n", WEXITSTATUS(status_code));
        //
        if(!line)
        {
            printf("Exit\n");
            ft_exit(0);
        }
        if (line[0] == '\0')
            continue;
        // print the args
        t_token *head = init_tokens(ft_strtrim(line, " "));
        head = init_tokens(join_tokens(head));
        add_t_type(head);
        split_args(head);
        

        // if (ft_strnstr(head->value, "exit", ft_strlen("exit")))
        // {
        //     if (head->args[1] != NULL)
        //         exit(ft_atoi(head->args[1]) % 256);
        //     else
        //         exit(0);
        // }

        //DONE: add the function that run the command in while with the paths splited 
        run_cmd(head, &envl, &exp_list,split_paths(get_PATH(envl)));
        // while (head)
        // {
        //     printf("#########################\n");
        //     printf("%i: Token => %s\n", i, head->value);
        //     if (head->args != NULL)
        //     {
        //         for (int i = 0; head->args[i]; i++)
        //         {
        //             printf("arg[%i] => %s\n", i, head->args[i]);
        //         }
        //     }
        //     else
        //         printf("args => %s\n", "NULL");
        //     printf("Type => %s\n", head->type);
        //     i++;
        //     head = head->next;
        // }
        add_history(line);
    }
    return (0);
}
