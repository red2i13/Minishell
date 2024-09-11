/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:19:34 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/09/11 19:57:19 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_list *envl)
{
	char	*path;

	path = NULL;
	if(!getenv("PATH"))
		return (DEFAULT_PATH_VALUE);
	while (envl)
	{
		path = ft_strnstr((char *)envl->content, "PATH=", 5);
		if (path)
			break ;
		envl = envl->next;
	}
	return (path);
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
	if (!ft_strncmp(cmd, "cd", 3))
		return (0);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (0);
	if (!ft_strncmp(cmd, "export", 7))
		return (0);
	if (!ft_strncmp(cmd, "unset", 6))
		return (0);
	if (!ft_strncmp(cmd, "env", 4))
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
		return (0);
	return (1);
}
