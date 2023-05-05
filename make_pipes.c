/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:39:37 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/05 20:56:39 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static int	**pipe_malloc_free(int **pfd, int i);
static int	**pipe_func_fail(int **pfd, int i);

int	**make_pipes(int num_of_pipe)
{
	int	i;
	int	**pfd;

	i = 0;
	pfd = malloc(sizeof(int *) * (num_of_pipe));
	if (pfd == 0)
		return (0);
	while (i < num_of_pipe)
	{
		pfd[i] = malloc(sizeof(int) * 2);
		if (pfd[i] == 0)
			return (pipe_malloc_free(pfd, i));
		if (pipe(pfd[i]) == -1)
			return (pipe_func_fail(pfd, i));
		i++;
	}
	return (pfd);
}

static int	**pipe_func_fail(int **pfd, int i)
{
	int	tmp;

	tmp = i;
	while (i--)
	{
		close(pfd[i][0]);
		close(pfd[i][1]);
	}
	return (pipe_malloc_free(pfd, tmp));
}

static int	**pipe_malloc_free(int **pfd, int i)
{
	while (i--)
		free(pfd[i]);
	free(pfd);
	return (0);
}
