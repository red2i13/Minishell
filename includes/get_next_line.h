/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:32:37 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/04 11:53:01 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ftt_strchr(const char *s, int c);
char	*ftt_strjoin(char const *s1, char const *s2);
size_t	ftt_strlen(const char *s);
void	*ftt_calloc(size_t nmemb, size_t size);
void	ftt_bzero(void *s, size_t n);

#endif
