/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/12 18:19:55 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

int	loop(int argc, char **argv, t_list	*lists[2])
{
	char	*line;
	t_token	*head;

	while (argc && argv)
	{
		signal_setup(2);
		restor_history(lists[0]);
		line = prompt(lists[0]);
		if (!line)
			return (ctl_exit(lists[1], lists[0]));
		if (line[0] == '\0')
			continue ;
		head = cmds_parse(line, lists[0]);
		if (heredoc(head, lists[0]) == 0)
		{
			list_clear(&head);
			write(1, "\n", 1);
			continue ;
		}
		ex_rm(&head, lists[0]);
		if (!head)
			continue ;
		excution(&head, &lists[0], &lists[1]);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*lists[2];

	set_up_env_exp(&lists[0], &lists[1], env);
	return (loop(argc, argv, lists));
}
