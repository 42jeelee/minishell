/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_close_and_free_things.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:11:45 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/27 17:07:55 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static void	exe_free_pipes(int **pfd, int num_of_pipe);

void	close_and_free_things(t_execute_arg *exe_arg)
{
	int	i;

	i = 0;
	parents_sig_end();
	if (exe_arg->fd[0] != -1)
		close(exe_arg->restore_fd[0]);
	if (exe_arg->fd[1] != -1)
		close(exe_arg->restore_fd[1]);
	while (exe_arg->tmp_name[i])
		free(exe_arg->tmp_name[i++]);
	free(exe_arg->tmp_name);
	i = 0;
	if (exe_arg->path != 0)
	{
		while (exe_arg->path[i])
			free(exe_arg->path[i++]);
		free(exe_arg->path);
	}
	free(exe_arg->pid);
	if (exe_arg->arg->num_of_cmd > 1)
		exe_free_pipes(exe_arg->pfd, exe_arg->arg->num_of_cmd);
}

static void	exe_free_pipes(int **pfd, int num_of_cmd)
{
	int	i;

	i = 0;
	while (i + 1 < num_of_cmd)
		free(pfd[i++]);
	free(pfd);
}
