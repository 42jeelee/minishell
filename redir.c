/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:43:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/22 17:07:46 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_one(char *file, int *fd, int *in_count);
static int	in_two(t_execute_arg *exe_arg, int *fd, int idx, int *in_count);
static int	out_one_two(char *file, int redir_type, int *fd, int *out_count);

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

int	redir(char **file, int *redir_type, int *fd, t_execute_arg *exe_arg)
{
	int		i;
	int		in_count;
	int		out_count;

	i = -1;
	in_count = 0;
	out_count = 0;
	while (file[++i])
	{
		if (redir_type[i] == INONE && in_one(file[i], fd, &in_count))
			return (1);
		else if (redir_type[i] == INTWO
			&& in_two(exe_arg, fd, exe_arg->child_num, &in_count))
			return (1);
		else if ((redir_type[i] == OUTONE || redir_type[i] == OUTTWO)
			&& out_one_two(file[i], redir_type[i], fd, &out_count))
			return (1);
	}
	return (0);
}

static int	in_two(t_execute_arg *exe_arg, int *fd, int idx, int *in_count)
{
	if (*in_count != 0)
		close(fd[0]);
	if (access(exe_arg->tmp_name[idx], R_OK) == -1)
		return (print_perror(exe_arg->tmp_name[idx]));
	fd[0] = open(exe_arg->tmp_name[idx], O_RDONLY);
	if (fd[0] < 0)
		return (print_perror(exe_arg->tmp_name[idx]));
	unlink(exe_arg->tmp_name[idx]);
	dup2(fd[0], 0);
	(*in_count)++;
	return (0);
}

static int	in_one(char *file, int *fd, int *in_count)
{
	if (*in_count != 0)
		close(fd[0]);
	if (access(file, R_OK) == -1)
		return (print_perror(file));
	fd[0] = open(file, O_RDONLY);
	if (fd[0] < 0)
		return (print_perror(file));
	dup2(fd[0], 0);
	(*in_count)++;
	return (0);
}

static int	out_one_two(char *file, int redir_type, int *fd, int *out_count)
{
	if (*out_count != 0)
		close(fd[1]);
	if (access(file, F_OK) == 0)
		if (access(file, W_OK) != 0)
			return (print_perror(file));
	if (redir_type == OUTONE)
	{
		unlink(file);
		fd[1] = open(file, O_WRONLY | O_CREAT, 0644);
	}
	else
		fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[1] < 0)
		return (print_perror(file));
	dup2(fd[1], 1);
	(*out_count)++;
	return (0);
}
