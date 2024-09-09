/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:19:25 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/09 17:48:03 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_func(int errnum, int exit_num)
{
	char	*str_err;

	str_err = strerror(errnum);
	printf("%s\n", str_err);
	(void)exit_num;
	// fix: if i run cd in the main process the shell exit
	// exit(exit_num);
}

void	error_exit(char *str, int exit_num)
{
	write(2, str, ft_strlen(str));
	exit(exit_num);
}
