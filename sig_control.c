/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:36:40 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/23 15:56:12 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	fork_sig_init(int sigquit)
{
	signal(SIGINT, SIG_DFL);
	if (sigquit)
		signal(SIGQUIT, SIG_DFL);
	else
		signal(SIGQUIT, SIG_IGN);
}

void	parents_sig_init(void)
{
	signal(SIGINT, SIG_IGN);
}

void	parents_sig_end(void)
{
	signal(SIGINT, sig_handler);
}
