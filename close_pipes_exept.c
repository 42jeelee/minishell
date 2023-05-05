/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_exept.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:40:54 by byejeon           #+#    #+#             */
/*   Updated: 2023/04/30 22:30:25 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

void	close_pipes_exept(int **pfd, int num_of_pipe, int *fd)
{
	int	i;

	i = 0;
	while (i < num_of_pipe)
	{
		if (pfd[i][0] != fd[0])
			close(pfd[i][0]);
		if (pfd[i][1] != fd[1])
			close(pfd[i][1]);
		i++;
	}
}
