/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:08:46 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/10 11:33:15 by rbenmakh         ###   ########.fr       */
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
	char	fn[16];

	while (head)
	{
		signal_setup(0);
		if (head->type == HEREDOC)
		{
			file_name = ran_file();
			ft_strlcpy(fn, file_name, 16);
			if (fork() == 0)
				fork_heredoc(fn, head, env);
			else
				wait(&status);
			free_arr(head->args);
			free_re(head, file_name);
			if (WEXITSTATUS(status) == 5)
				return (g_status = 130, 0);
		}
		head = head->next;
	}
	return (1);
}
