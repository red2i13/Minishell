/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:02:04 by ysahraou          #+#    #+#             */
/*   Updated: 2024/09/10 10:14:44 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_up_env_exp(t_list **envl, t_list **exp_list, char **env)
{
	char	*tmp;
	char	*val;

	*envl = setup_env(env);
	*exp_list = setup_exp(*envl);
	if (*envl)
	{
		val = ft_itoa(ft_atoi(tmp = get_var("SHLVL", *envl)) + 1);
		free(tmp);
		export(exp_list, envl, "SHLVL=", val);
		free(val);
	}
	if (*envl == NULL)
	{
		export(exp_list, envl, "PWD=", tmp = getcwd(NULL, 0));
		export(exp_list, envl, "SHLVL=", "1");
		export(exp_list, envl, "_=", "/usr/bin/env");
		free(tmp);
	}
}
