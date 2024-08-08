/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:49:55 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/08 09:53:33 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int arr_size(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return 0;
    while (arr[i])
        i++;
    return i;
}

char **ft_realloc(char *arg, char **old_arr)
{
    char **new_arr = malloc(sizeof(char *) * (arr_size(old_arr) + 2));
    int i;

    i = 0;
    if (old_arr)
    {
      while (old_arr[i])
      {
          new_arr[i] = old_arr[i];
          i++;
      }
    }
    new_arr[i++] = arg;
    new_arr[i] = NULL;
    free(old_arr);
    return new_arr;
}


t_token *init_tokens(char **args)
{
    int i[2];
    t_token *head;

    head = NULL;
    i[0] = 0;
    i[1] = 0;
    char **new_args = NULL;
    while (args[i[0]])
    {
        new_args = ft_realloc(args[i[0]], new_args);
        i[0]++;
    }
    for (int i = 0; new_args[i]; i++)
        printf("[]===%s===]\n", new_args[i]);
    return head;
}