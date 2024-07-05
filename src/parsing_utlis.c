/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:37 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/05 10:43:43 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_PATH(char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH", 4);
		if (path)
			break ;
		i++;
	}
	return path;
}

char	**split_paths(char *paths)
{
	int		i;
    char	*first_part;
	char	**the_paths;

	i = 0;
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] && paths[i] != '=')
		i++;
	first_part = ft_substr(&paths[i + 1], 0, ft_strlen(paths));
	the_paths = ft_split(first_part, ':');
	free(first_part);
	return (the_paths);
}

char *check_cmd(char *cmd, char **paths)
{
    int num; 
    int i ;
    char *tmp;
    i= 0;
    num = -1;
    while(paths[i])
    {
		tmp = ft_strjoin( "/", cmd);
        tmp = ft_strjoin(paths[i], tmp);
        //printf("%s\n", tmp);
        num = access(tmp, F_OK | X_OK);
		if(!num)
			return(tmp);
		free(tmp);
        i++;
    }
    if(num == -1)
        error_func(errno, 2);
		return(0);
}


void	split_args(t_token *head)
{
	while (head)
	{
		if (ft_strnstr(head->type, "CMD", 3))
		{
			head->args = ft_split(head->value, ' ');
		}
		else
			head->args = NULL;
		head = head->next;
	}
}