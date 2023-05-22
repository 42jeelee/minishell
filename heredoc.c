/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:52:42 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/22 20:26:23 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

void	unlink_tmp_files(t_cmds *cmds, t_execute_arg *exe_arg)
{
	int	i;

	i = 0;
	while (cmds)
	{
		unlink(exe_arg->tmp_name[i++]);
		cmds = cmds->next;
	}
}

int	heredoc(t_cmds *cmds, t_execute_arg *exe_arg)
{
	pid_t			pid;
	int				stat_loc;
	struct termios	old_term;

	parents_sig_init();
	no_echoctl(&old_term);
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
	change_term(&old_term);
	if (WIFSIGNALED(stat_loc))
	{
		unlink_tmp_files(cmds, exe_arg);
		exe_arg->exit_code |= 1 << 8;
		ft_putchar_fd('\n', 1);
	}
	parents_sig_end();
	return (stat_loc);
}
