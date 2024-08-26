/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:26:18 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/08/26 09:56:21 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char  *last_io(t_token * head, int type)
{
	char *file;

	file = NULL;
	while(head)
	{
		if(head->args[0][0] == '<' && type)
			file = head->next->args[0];
		else if(head->args[0][0] == '>' && !type)
			file = head->next->args[0];
		head = head->next;
	}
	return(file);
}
int redir_output(char *filename, int flag)
{
	int fd;
	
	if(flag == 1)
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
   if (dup2(fd, 1) == -1) 
   {
        perror("dup2");
        close(fd);
        return -1;
    }
	close (fd);
	return(0);
}

int redir_input(char *filename)
{
	int fd;
	
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		exit(1);	
	}
	dup2(fd, STDIN_FILENO);
	close (fd);
	return(0);
}