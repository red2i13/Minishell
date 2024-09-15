/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:06 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/15 15:16:44 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_status;

/*
void	p_list(t_token *head)
{
	while (head)
	{
		printf("n_start==========================\n");
		for (int i = 0; head->args[i]; i++)
			printf("{%i}[%s]\n", i, head->args[i]);
		if (head->args[head->arg_size] == NULL)
			printf("[NULL]\n");
		printf("%i\n", head->arg_size);
		if (head->type == HEREDOC)
			printf("HEREDOC\n");
		if (head->type == RED)
			printf("RED\n");
		if (head->type == PIPE)
			printf("PIPE\n");
		if (head->type == CMD)
			printf("CMD\n");
		if (head->type == FILE_N)
			printf("FILE_N\n");
		printf("index = %i\n", head->index);
		printf("n_end==========================\n");
		head = head->next;
	}
}
*/
int	loop(int argc, char **argv, t_list *lists[2])
{
	char	*line;
	t_token	*head;

	restor_history(lists[0]);
	while (argc && argv)
	{
		signal_setup(2);
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
