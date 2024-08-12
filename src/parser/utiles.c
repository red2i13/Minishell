/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:16:11 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/11 11:19:57 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_arr(char **arr)
{
    int i;

    i = 0;
    if (arr == NULL)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}