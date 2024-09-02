/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:11:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/02 19:51:22 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void restor_history(t_list  *envl)
{
    char *file_n;
    char *tmp;
    int fd;
    char *line;

    tmp = get_var("HOME", envl);
    if (tmp == NULL)
        return ;
    file_n = ft_strjoin(tmp, "/.minishell_history");
    free(tmp);
    if (access(file_n, F_OK | R_OK | W_OK))
        fd = open(file_n, O_RDWR | O_APPEND | O_CREAT, 0777);
    else
        fd = open(file_n, O_RDWR | O_APPEND);
    line = get_next_line(fd);
    while (line)
    {
        line[ft_strlen(line)-1] = '\0';
        add_history(line);
        free(line);
        line = get_next_line(fd);
    }
    free(file_n);
    close(fd);
}

int setup_h(char *line, t_list  *envl)
{
    char *file_n;
    char *tmp;
    int fd;

    tmp = get_var("HOME", envl);
    if (tmp == NULL)
        return (-1);
    file_n = ft_strjoin(tmp, "/.minishell_history");
    free(tmp);
    if (access(file_n, F_OK | R_OK | W_OK))
        fd = open(file_n, O_RDWR | O_APPEND | O_CREAT, 0777);
    else
        fd = open(file_n, O_RDWR | O_APPEND);
    add_history(line);
    line = ft_strjoin(line, "\n");
    write(fd, line, ft_strlen(line));
    free(line);
    free(file_n);
    close(fd);
    return 0;
}
