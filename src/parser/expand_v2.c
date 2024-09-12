/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:34:07 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/12 12:31:38 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_expand(char *fr, char *brev, char *var, char *str)
{
	free(fr);
	free(brev);
	free(var);
	free(str);
}

char	**join_and_split(char *str, char *set)
{
	int		len;
	int		i[3];
	char	**arr;

	len = 0;
	if (str[0] == '\0')
		return	(NULL);
	len = count_words(str, set, i);
	arr = malloc(sizeof(char *) * (len + 1));
	arr = fill_arr(arr, str, i);
	arr[len] = NULL;
	return (arr);
}

char	*expand(char *str, t_list *env, int *q, char ***temp)
{
	char	*t;

	while (str && str[0] && str[q[2]])
	{
		q[0] = (q[0] + (!q[1] && str[q[2]] == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && str[q[2]] == '\"')) % 2;
		if (!q[0] && str[q[2]] == '$' && str[q[2] + 1]
			&& !ft_strchr("\\#=+-^[].,!@;*%~&{}() \t", str[q[2] + 1])
			&& !(ft_strchr("\"", str[q[2] + 1]) && q[1]))
		{
			if (!q[0] && !q[1] && temp)
			{
				t = vars_sub(str, q[2] + 1, env);
				*temp = join_and_split(t, " \t");
				return (t);
			}
			else
				return (expand(vars_sub(str, q[2] + 1, env), env, q, temp));
		}
		q[2]++;
	}
	if (temp)
		*temp = NULL;
	return (str);
}
