#include "../includes/minishell.h"

// #include <unistd.h>
// #include <stdio.h>
// #include <sys/types.h>
// #include <dirent.h>

// typedef struct  s_env
// {
//     char *value;
//     struct  s_env *next;
// }               t_env;

// int main(int ac, char **av, char **env)
// {
//     // char *path = getcwd(0, 0);

//     // printf("%s\n", path);
//     // opendir("../");
//     // path = getcwd(0, 0);

//     // printf("%s\n", path);
//     t_list *envp;

//     envp = NULL; 

//     int i = 0;
//     while(env[i])
//     {
//         if(ft_strnstr(env[i], "PWD", 3))
//             ft_lstadd_back(&envp, ft_lstnew(ft_substr(env[i], 0, ft_strlen(env[i]))));
//         i++;
//     }
//     printf("%s", (char *)envp->content);
// }
//test2
void func(char **env)
{
    
}
int main(int ac, char **av, char **env){
    int i ;
    int j ;
    char *ptr;
    t_list *envp;
    
    i= 0;
    envp = NULL; 
    while(env[i + 1])
    {
        j = i + 1;
        while(env[j])
        {
            if(ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
            {
                ptr = env[i];
                env[i] = env[j];
                env[j] = ptr;
            }
            j++;
        }
        i++;
    }
    for(int k = 0; env[k]; k++)
    {
        printf("%s\n", env[k]);
    }
}

