/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:14:44 by ysahraou          #+#    #+#             */
/*   Updated: 2024/08/31 15:03:19 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void sighandler(int signum) 
{
    if(signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void sig_exit(int num)
{
    (void)num;
    exit(5);
}

void signal_setup(int n)
{
    if (n == 1)
    {
        signal(SIGINT, sig_exit);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (n == 2)
    {
        signal(SIGINT, sighandler);
        signal(SIGQUIT, SIG_IGN);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
}