/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:46 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/13 11:21:30 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ran_file(void)
{
    int fd;
    char *s;
    char *tmp;
    int i[2];
    char *buff;
    
    i[0] = 0;
    i[1] = 0;
    buff = malloc(100 * sizeof(char));
    s = malloc(11 * sizeof(char));
    fd = open("/dev/random", O_RDONLY);
    read(fd, buff, 100);
    while (i[0] < 100)
    {
        if (ft_isalnum(buff[i[0]]) && i[1] < 10)
            s[i[1]++] = buff[i[0]];
        i[0]++;
    }
    s[i[1]] = '\0';
    tmp = s;
    s = ft_strjoin("/tmp/", s);
    free(tmp);
    free(buff);
    close(fd);
    return(s);
}
void read_put(char *file_name, char *del)
{
    char *str;
    char *tmp;
    int fd;

    fd = open(file_name, O_CREAT | O_RDWR , 0777);
    // the under line use to print the file desc
    // printf("%i\n", fd);
    while(1)
    {
        str = readline(">");
        if (!ft_strncmp(str, del, ft_strlen(str)) && ft_strlen(str) != 0)
            break;
        tmp = str;
        str = ft_strjoin(str, "\n");
        write(fd, str, ft_strlen(str));
       free(tmp);
    }
    close(fd);
}

void heredoc(t_token *head)
{
    char *file_name;
    (void)head;
    
    file_name = ran_file();
    // the under line use to print the file name 
    // printf("%s\n", file_name);
    while (head)
    {
        if (head->type == HEREDOC)
        {
            read_put(file_name, head->next->args[0]);
            free_arr(head->args);
            head->args = malloc(sizeof(char *) * 2);
            head->args[0] = ft_strdup("<");
            head->args[1] = NULL;
            head->type = RED;
            head->arg_size = 1;
            free_arr(head->next->args);
            head->next->args = malloc(sizeof(char *) * 2);
            head->next->args[0] = file_name;
            head->next->args[1] = NULL;
            head->next->type = FILE_N;
        }
        head = head->next;   
    }
}
