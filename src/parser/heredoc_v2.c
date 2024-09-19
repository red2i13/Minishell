/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:11:07 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/19 12:54:00 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_int(int *i)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
}

int	read_put(char *file_name, char *del, int q, t_list *env)
{
	char	*str;
	int		i[3];
	int		fd;

	fd = open(file_name, O_CREAT | O_RDWR, 0777);
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			write(1, "minishell:warning: here-doc delimited by EOF!\n", 47);
			ft_lstclear(&env, free);
			return (1);
		}
		if (ff_strncmp(str, del, ft_strlen(del)) || (ft_strlen(str) == 0
				&& ft_strlen(del) == 0))
			break ;
		set_int(i);
		if (q == 0)
			str = expand_h(str, env, i, NULL);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	return (close(fd), 0);
}

void	fork_heredoc(char *fn, t_token *head, t_list *list[2], t_token	*tmp)
{
	signal_setup(1);
	if (is_q(head->next->args[0]))
	{
		head->next->args[0] = rm_quote(head->next->args[0]);
		if (read_put(fn, head->next->args[0], 1, list[0]))
		{
			list_clear(&tmp);
			ft_lstclear(&list[1], free);
			exit(0);
		}
	}
	else
	{
		if (read_put(fn, head->next->args[0], 0, list[0]))
		{
			list_clear(&tmp);
			ft_lstclear(&list[1], free);
			exit(0);
		}
	}
	ft_lstclear(&list[0], free);
	ft_lstclear(&list[1], free);
	list_clear(&tmp);
	exit(0);
}

void	free_re(t_token *head, char *file_name)
{
	head->args = malloc(sizeof(char *) * 2);
	head->args[0] = ft_strdup("<");
	head->args[1] = NULL;
	head->type = RED;
	head->arg_size = 1;
	free(head->next->args[0]);
	head->next->args[0] = file_name;
	head->next->type = FILE_N;
}
