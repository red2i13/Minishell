/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:09 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/11 15:37:55 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*color_g(char *user, char *exit_s)
{
	char	*temp;
	char	*ret;

	ret = ft_strjoin(user, "@\033[0;32mminishell [");
	temp = ret;
	ret = ft_strjoin(ret, exit_s);
	free(temp);
	temp = ret;
	ret = ft_strjoin(ret, "]→\033[0m ");
	free(temp);
	return (ret);
}

char	*color_r(char *user, char *exit_s)
{
	char	*temp;
	char	*ret;

	ret = ft_strjoin(user, "@\033[0;32mminishell\033[0;31m [");
	temp = ret;
	ret = ft_strjoin(ret, exit_s);
	free(temp);
	temp = ret;
	ret = ft_strjoin(ret, "]→\033[0m ");
	free(temp);
	return (ret);
}

char	*get_user(t_list *env, int err)
{
	char	*user;
	char	*tmp;
	char	*exit_s;

	exit_s = ft_itoa(g_status);
	user = get_var("USER", env);
	if (!user)
		user = ft_strdup("gest");
	tmp = user;
	user = ft_strjoin("\033[0;36m", user);
	free(tmp);
	tmp = user;
	if (!err)
		user = color_g(user, exit_s);
	else
		user = color_r(user, exit_s);
	free(tmp);
	free(exit_s);
	return (user);
}

char	*prompt(t_list *env)
{
	char	*user;
	char	*line;

	if (!g_status)
	{
		user = get_user(env, 0);
		line = readline(user);
	}
	else
	{
		user = get_user(env, 1);
		line = readline(user);
	}
	free(user);
	return (line);
}
