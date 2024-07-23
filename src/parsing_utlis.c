/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:19:34 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/07/23 19:14:03 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char *get_PATH(char **env)
// {
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	path = NULL;
// 	while (env[i])
// 	{
// 		path = ft_strnstr(env[i], "PATH=", 5);
// 		if (path)
// 			break ;
// 		i++;
// 	}
// 	return path;
// }
//2nd version
char *get_PATH(t_list *envl)
{
	char	*path;
	int		i;

	i = 0;
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
char *check_cmd(char *cmd, char **paths)
{
    int num; 
    int i ;
    char *tmp;
    
	i = 0;
    num = -1;
	if(!paths)
		return(NULL);
	else if(!access(cmd,F_OK | X_OK))
		return(cmd);
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
	//if the command not found return 127 as exit code
    if(num == -1 && check_builtin(cmd))
	{
        //this function should store the exit code if the command is not found
		printf("$: command not found: %s\n", cmd);
		//error_func(errno, 127);
	}
	return(0);
}
void	split_args(t_token *head)
{
	while (head)
	{
		if (ft_strnstr(head->type, "CMD", 3) && head->q == 0)
		{
				head->args = ft_split(head->value, ' ');
		}
		else
			head->args = NULL;
		head = head->next;
	}
}
// int	check_quotes(char *cmd)
// {
// 	int count; 
// 	count = 0;

// 	while(*cmd)
// 	{
// 		if(*cmd == '\'' || *cmd == '"')
// 			count++;
// 		cmd++;
// 	}
// 	return(count);
// }
// void split_quotes(char **args)
// {
// 	int i ;
// 	char *tmp;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if(args[i][0] == '\'' || args[i][0] == '"')
// 		{
// 			tmp = args[i];
			
// 		}
// 	}
		
// }
//
// void	split_args(t_token *head)
// {
// 	while (head)
// 	{
// 		if (ft_strnstr(head->type, "CMD", 3))
// 		{
// 			if(check_quotes(head->value) == 2 && (head->value[0] == '\'' || head->value[0] == '"'))
// 				head->args = &head->value;
// 			else
// 				split_quotes(head->args);
// 		}
// 		else
// 			head->args = NULL;
// 		head = head->next;
// 	}
// }