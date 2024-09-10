/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:50:47 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/10 10:02:00 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipe	*init_pipes(int p)
{
	t_pipe	*fdt;
	int		i;

	i = 0;
	fdt = malloc(sizeof(t_pipe) * p);
	if (!fdt)
		return (0);
	while (i < p)
	{
		if (pipe(fdt[i].fd) == -1)
		{
			(void)fdt;
		}
		i++;
	}
	return (fdt);
}

void	pipe_redirection(t_token *head)
{
	int		r;
	t_token	*tmp;

	r = check_redir(head, 0);
	if (r || check_redir(head, 1))
	{
		tmp = head;
		while (tmp)
		{
			if (tmp->args[0] && tmp->args[0][0] == '|')
				break ;
			else if (tmp->args[0] && tmp->args[0][0] == '>')
				redir_output(tmp->next->args[0], r);
			else if (tmp->args[0] && tmp->args[0][0] == '<')
				redir_input(tmp->next->args[0]);
			tmp = tmp->next;
		}
	}
}

void	check_invalid_cmd(t_token *head)
{
	if (!head->args[0] || (head->args[0] && head->args[0][0] == '>')
		|| (head->args[0] && head->args[0][0] == '<'))
		exit(0);
}

void	run(t_token *head, t_list **envl, t_list **exp_list, char **paths)
{
	char	*cmd;
	char	**env;

	pipe_redirection(head);
	check_invalid_cmd(head);
	if (ft_strnstr(head->args[0], "exit", ft_strlen("exit")))
		ft_exit(head);
	else if (!builtin(head, envl, exp_list))
	{
		g_status = 0;
		exit(0);
	}
	env = convert_to_array(*envl);
	cmd = check_cmd(head->args[0], paths);
	if (!cmd)
		exit(127);
	else if (execve(cmd, head->args, env) == -1)
	{
		error_and_exit(1);
	}
	if (cmd != head->args[0])
		free(cmd);
	free_arr(paths);
	free_arr(env);
	exit(0);
}

int	exec_pipes(t_token *head, t_list **envl, t_list **exp_list, char **paths)
{
	int		i[5];
	t_pipe	*fdt;

	init_var_pipe(head, i);
	fdt = init_pipes(i[3]);
	while (i[0] <= i[3])
	{
		i[1] = fork();
		if (!i[1])
		{
			if (i[0] != i[3])
				dup2(fdt[i[0]].fd[1], STDOUT_FILENO);
			if (i[0] > 0)
				dup2(fdt[i[0] - 1].fd[0], STDIN_FILENO);
			close_unused_fd(fdt, i[3]);
			run(head, envl, exp_list, paths);
		}
		else if (i[0] == i[3])
			i[4] = i[1];
		next_cmd(&head);
		i[0]++;
	}
	close_unused_fd(fdt, i[3]);
	free_and_wait(fdt, i[3], i[4]);
	return (free_arr(paths), 0);
}
