/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:46 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/04 12:28:49 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ran_file(void)
{
	int		fd;
	char	*s;
	char	*tmp;
	int		i[2];
	char	*buff;

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
	return (s);
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

int	is_q(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	heredoc(t_token *head, t_list *env)
{
	char	*file_name;
	int		status;

	while (head)
	{
		signal_setup(0);
		if (head->type == HEREDOC)
		{
			file_name = ran_file();
			if (fork() == 0)
				fork_heredoc(file_name, head, env);
			else
				wait(&status);
			if (WEXITSTATUS(status) == 5)
				return (0);
			free_arr(head->args);
			free_re(head, file_name);
		}
		head = head->next;
	}
	return (1);
}
