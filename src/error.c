/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:19:25 by ysahraou          #+#    #+#             */
/*   Updated: 2024/06/29 10:29:08 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void error_func(int errnum, int exit_num)
{
    char str_err;
    
    str_err = strerror(errnum);
    printf("%s", str_err);
    exit(exit_num);
}
