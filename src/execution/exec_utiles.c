/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:46:01 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/14 10:30:51 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_status = WTERMSIG(status) + 128;
		if (g_status == 130)
			write(1, "\n", 1);
	}
}
