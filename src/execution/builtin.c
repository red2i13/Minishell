/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:43:12 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/15 19:50:52 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_nl(char *s)
{
	if (*s == '\0')
		return (1);
	while (*s)
	{
		if (*s != 'n')
			return (1);
		s++;
	}
	return (0);
}

void	echo(char **cmd)
{
	int	i;
	int	flag;
	int	flag2;

	i = 1;
	flag = 0;
	flag2 = 0;
	while (cmd[i])
	{
		if (!flag2 && cmd[i][0] == '-' && !check_nl(&cmd[i][1]))
		{
			flag = 1;
		}
		else
		{
			if (i > 1 && flag2)
				printf(" ");
			flag2 = 1;
			printf("%s", cmd[i]);
		}
		i++;
	}
	if (!flag)
		printf("\n");
}

void	printf_export(char *str, int is_equal)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	printf("declare -x %.*s", i, str);
	if (str[i] && !is_equal)
		printf("=\"%s\"", str + i + 1);
	printf("\n");
}

void	while_print_export(t_list *exp_list)
{
	while (exp_list)
	{
		printf_export((char *)exp_list->content, exp_list->is_equal);
		exp_list = exp_list->next;
	}
}

void	ft_exit(t_token *head)
{
	long	val;

	if (!head->args[1])
	{
		list_clear(&head);
		exit(g_status);
	}
	val = ft_atoi(head->args[1]);
	if ((!val && head->args[1][0] != '0') || (!val && head->args[1][0] == '-')
		|| val == __LONG_MAX__)
	{
		write(2, "minishell: exit: numeric argument required\n", 44);
		exit(2);
	}
	else if (head->args[2])
	{
		write(2, "exit\nminishell: exit: too many arguments\n", 42);
		return ;
	}
	else if (val != 0)
		exit(val % 256);
}
