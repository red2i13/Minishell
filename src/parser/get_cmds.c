/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:07:17 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/07 14:39:14 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cmds_trim(char *line, int *i, char **arr)
{
	int	nwords;

	i[0] = 0;
	i[1] = 0;
	nwords = count_words(line, " \t", i);
	if (nwords < 0)
		return (p_err(nwords), NULL);
	if (nwords == 0)
		return (NULL);
	arr = malloc(sizeof(char *) * (nwords + 1));
	if (arr == NULL)
		return (NULL);
	arr = fill_arr(arr, line, i);
	arr[nwords] = NULL;
	return (arr);
}

char	**get_cmds(char *line, t_list *envl)
{
	char	**arr;
	int		i[3];
	int		j;
	int		len;
	char	**mini;

	arr = NULL;
	setup_h(line, envl);
	arr = cmds_trim(line, i, arr);
	j = 0;
	len = 0;
	while (arr && arr[j])
	{
		len = 0;
		len = count_words_2(arr[j], "<|>", i);
		mini = malloc(sizeof(char *) * (len + 1));
		mini = fill_arr_2(mini, arr[j], i, "<|>");
		arr = join_cmds(arr, mini, j);
		j++;
	}
	return (arr);
}
