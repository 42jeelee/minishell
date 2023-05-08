/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:04:11 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/08 01:15:17 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_term(struct termios *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void	no_echoctl(struct termios *old_term)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, old_term);
	term = *old_term;
	term.c_lflag &= ~ECHOCTL;
	change_term(&term);
}
