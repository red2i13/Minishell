/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:19:34 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/08/08 22:29:17 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char *get_PATH(t_list *envl)
{
	char	*path;
	// int		i;

	// i = 0;
	path = NULL;
	while (envl)
	{
		path = ft_strnstr((char*)envl->content, "PATH=", 5);
		if (path)
			break ;
		envl = envl->next;
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
int	check_builtin(char *cmd)
{
	char *str;

	str = "cd";
	if(!ft_strncmp(cmd, str, 3))
		return(0);
	str = "pwd";
	if(!ft_strncmp(cmd, str, 4))
		return(0);
	str = "export";
	if(!ft_strncmp(cmd, str, 7))
		return(0);
	str = "unset";
	if(!ft_strncmp(cmd, str, 6))
		return(0);
	str = "env";
	if(!ft_strncmp(cmd, str, 4))
		return(0);
	str = "echo";
	if(!ft_strncmp(cmd, str, 5))
		return(0);
	str = "exit";
	if(!ft_strncmp(cmd, str, 5))
		return(0);
	return(1);
}
