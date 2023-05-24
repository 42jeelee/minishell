/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:56:23 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/24 14:56:54 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

void	pipe_redir(int **pfd, int i, int num_of_cmd, int *fd)
{
	if (i != 0)
	{
		fd[0] = pfd[i -1][0];
		dup2(pfd[i -1][0], 0);
	}
	if (i != num_of_cmd - 1)
	{
		fd[1] = pfd[i][1];
		dup2(pfd[i][1], 1);
	}
}
