/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:26:18 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/08/09 01:13:00 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirection(char *filename, int flag)
{
	int fd;
	
	if(flag == 1)
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(filename, O_APPEND | O_RDWR, 0644);
   if (dup2(fd, 1) == -1) 
   {
        perror("dup2");
        close(fd);
        return -1;
    }
	close (fd);
	return(0);
}