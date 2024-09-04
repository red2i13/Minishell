/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 08:10:13 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/04 12:43:07 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(char **arr)
{
	int	count;

	count = 0;
	while (arr && arr[count])
		count++;
	return (count);
}

char	**join_cmds(char **big, char **mini, int pos)
{
	int		count[2];
	char	**ret_arr;
	int		i[3];

	count[0] = count_cmd(big);
	count[1] = count_cmd(mini);
	ret_arr = malloc(sizeof(char *) * (count[0] + count[1]));
	i[0] = 0;
	i[2] = 0;
	while (big[i[0]])
	{
		if (i[0] != pos)
			ret_arr[i[2]++] = big[i[0]];
		else
		{
			i[1] = 0;
			while (mini && mini[i[1]])
				ret_arr[i[2]++] = mini[i[1]++];
			free(big[i[0]]);
		}
		i[0]++;
	}
	ret_arr[i[2]] = NULL;
	return (free(big), free(mini), ret_arr);
}
