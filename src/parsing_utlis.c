/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:37 by ysahraou          #+#    #+#             */
/*   Updated: 2024/07/08 12:07:56 by rbenmakh         ###   ########.fr       */
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
int	check_quotes(char *cmd)
{
	int count; 
	count = 0;

	while(*cmd)
	{
		if(*cmd == '\'' || *cmd == '"')
			count++;
		cmd++;
	}
	return(count);
}
void split_quotes(char **args)
{
	int i ;
	char *tmp;

	i = 0;
	while (args[i])
	{
		if(args[i][0] == '\'' || args[i][0] = '"')
		{
			tmp = args[i];
			
		}
	}
		
}

void	split_args(t_token *head)
{
	while (head)
	{
		if (ft_strnstr(head->type, "CMD", 3))
		{
			if(check_quotes(head->value) == 2 && (head->value[0] == '\'' || head->value[0] == '"'))
				head->args = ft_split(head->value, ' ');
			else
				split_quotes(head->args);
		}
		else
			head->args = NULL;
		head = head->next;
	}
}