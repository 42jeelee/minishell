/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:43:29 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/22 19:47:32 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

void	wait_childs(t_execute_arg *exe_arg)
{
	while (exe_arg->i < exe_arg->child_num)
	{
		waitpid(exe_arg->pid[exe_arg->i++], &exe_arg->exit_code, WUNTRACED);
		if (WIFSIGNALED(exe_arg->exit_code))
		{
			if (WTERMSIG(exe_arg->exit_code) == SIGQUIT)
				ft_putstr_fd("QUIT: 3", STDOUT_FILENO);
			exe_arg->exit_code |= (128 + WTERMSIG(exe_arg->exit_code)) << 8;
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
}
