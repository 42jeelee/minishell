/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:43:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/06 19:01:49 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	in_one(char *file, int *fd, int *in_count);
static void	out_one_two(char *file, int redir_type, int *fd, int *out_count);

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

void	redir(char **file, int *redir_type, int *fd)
{
	int		i;
	int		in_count;
	int		out_count;

	i = 0;
	in_count = 0;
	out_count = 0;
	while (file[i])
	{
		if (redir_type[i] == INONE)
			in_one(file[i], fd, &in_count);
		else if (redir_type[i] == OUTONE || redir_type[i] == OUTTWO)
			out_one_two(file[i], redir_type[i], fd, &out_count);
		i++;
	}
}

static void	in_one(char *file, int *fd, int *in_count)
{
	if (*in_count != 0)
		close(fd[0]);
	if (access(file, R_OK) == -1)
	{
		write
		exit(print_perror(file));
	}
	fd[0] = open(file, O_RDONLY);
	if (fd[0] < 0)
		exit(print_perror(file));
	dup2(fd[0], 0);
	(*in_count)++;
}

static void	out_one_two(char *file, int redir_type, int *fd, int *out_count)
{
	if (*out_count != 0)
		close(fd[1]);
	if (access(file, F_OK) == 0)
		if (access(file, W_OK) != 0)
			exit(print_perror(file));
	if (redir_type == OUTONE)
	{
		unlink(file);
		fd[1] = open(file, O_WRONLY | O_CREAT, 0644);
	}
	else
		fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[1] < 0)
		exit(print_perror(file));
	dup2(fd[1], 1);
	(*out_count)++;
}
