/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:46 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/28 14:23:15 by ysahraou         ###   ########.fr       */
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

int	ff_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

void read_put(char *file_name, char *del, int q, t_list *env)
{
    char *str;
    int i[3];
    char *tmp;
    int fd;

    fd = open(file_name, O_CREAT | O_RDWR , 0777);
    // the under line use to print the file desc
    // printf("%i\n", fd);
    while(1)
    {
        str = readline(">");
        if (ff_strncmp(str, del, ft_strlen(del)) && ft_strlen(str) != 0)
            break;
        tmp = str;
        i[0] = 0;
        i[1] = 0;
        i[2] = 0;
        if (q == 0)
            str = expand(str, env, i, NULL);
        str = ft_strjoin(str, "\n");
        write(fd, str, ft_strlen(str));
        free(tmp);
    }
    close(fd);
}

int is_q(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
            return (1);
        i++;
    }
    return (0);
}

void heredoc(t_token *head, t_list *env)
{
    char *file_name;
    (void)head;
    

    // the under line use to print the file name 
    // printf("%s\n", file_name);
    while (head)
    {
        if (head->type == HEREDOC)
        {
            file_name = ran_file();
            if (is_q(head->next->args[0]))
            {
                head->next->args[0] = rm_quote(head->next->args[0]);
                read_put(file_name, head->next->args[0], 1, env);
            }
            else
                read_put(file_name, head->next->args[0], 0, env);
            free_arr(head->args);
            head->args = malloc(sizeof(char *) * 2);
            head->args[0] = ft_strdup("<");
            head->args[1] = NULL;
            head->type = RED;
            head->arg_size = 1;
            free(head->next->args[0]);
            head->next->args[0] = file_name;
            head->next->type = FILE_N;
        }
        head = head->next;   
    }
}
