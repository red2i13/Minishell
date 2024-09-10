/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/10 10:22:17 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*head;
	t_list	*envl;
	t_list	*exp_list;

	set_up_env_exp(&envl, &exp_list, env);
	while (argc && argv)
	{
		signal_setup(2);
		restor_history(envl);
		line = prompt(envl);
		if (!line)
			return (ctl_exit(exp_list, envl));
		if (line[0] == '\0')
			continue ;
		head = cmds_parse(line, envl);
		if (heredoc(head, envl) == 0)
		{
			list_clear(head);
			head = NULL;
			g_status = 130;
			continue ;
		}
		ex_rm(&head, envl);
		if (!head)
			continue ;
		else if (check_pipe(head))
			exec_pipes(head, &envl, &exp_list, split_paths(get_path(envl)));
		else if (check_redir(head, 0) || check_redir(head, 1))
			redirection(head, &envl, &exp_list);
		else
			run_cmd(head, &envl, &exp_list, split_paths(get_path(envl)));
		list_clear(head);
		head = NULL;
	}
	return (0);
}
