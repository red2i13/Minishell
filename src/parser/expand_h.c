/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:43:24 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/12 18:11:30 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_h(char *str, t_list *env, int *q, char ***temp)
{
	while (str && str[0] && str[q[2]])
	{
		if (str[q[2]] == '$' && str[q[2] + 1]
			&& !ft_strchr("\\#=+-^[].,!@;*%~&{}() \t", str[q[2] + 1])
			&& !(ft_strchr("\"", str[q[2] + 1]) && q[1]))
			return (expand_h(vars_sub(str, q[2] + 1, env), env, q, temp));
		q[2]++;
	}
	if (temp)
		*temp = NULL;
	return (str);
}
