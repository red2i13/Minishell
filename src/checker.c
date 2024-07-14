/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 09:32:38 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/14 09:31:46 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void check_syntax(char *line)
{
    if (line[0] == '|' || ft_strnstr(line, "||", ft_strlen(line)))
        error_exit("Minishell: syntax error near unexpected token `|'\n", 2);
    else if (ft_strnstr(line, ">>>", ft_strlen(line)))
        error_exit("Minishell: syntax error near unexpected token `>'\n", 2);
    else if (ft_strnstr(line, "<<<", ft_strlen(line)))
        error_exit("Minishell: syntax error near unexpected token `<'\n", 2);
}