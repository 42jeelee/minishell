/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:52:42 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/22 18:27:23 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

int	heredoc(t_cmds *cmds, t_execute_arg *exe_arg)
{
	pid_t	pid;
	int		stat_loc;

	parents_sig_init();
	pid = fork();
	if (pid == 0)
	{
		fork_sig_init();
		make_and_write_tmp_files(cmds, exe_arg);
		if (exe_arg->exit_code > 0)
			exit(1);
		exit(0);
	}
	waitpid(pid, &stat_loc, WUNTRACED);
	if (WIFSIGNALED(stat_loc))
	{
		exe_arg->exit_code = 1;
		ft_putchar_fd('\n', 1);
	}
	parents_sig_end();
	return (WEXITSTATUS(stat_loc));
}
