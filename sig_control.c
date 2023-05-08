/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:36:40 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/08 14:29:43 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_init(t_arg *arg)
{
	arg->old_sigint = signal(SIGINT, sig_handler);
	arg->old_sigquit = signal(SIGQUIT, SIG_IGN);
}

void	fork_sig_init(t_arg *arg)
{
	signal(SIGINT, arg->old_sigint);
	signal(SIGQUIT, arg->old_sigquit);
}
