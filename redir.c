/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:43:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/24 15:32:59 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_one(char *file, int *fd, int *in_count);
static int	in_two(t_execute_arg *exe_arg, int *fd, int *in_count);
static int	out_one_two(char *file, int redir_type, int *fd, int *out_count);
static int	last_heredoc_idx(char **file, int *redir_type);

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
		else if (redir_type[i] == INTWO)
		{
			if (in_two(exe_arg, fd, &in_count) != 0)
				return (1);
			if (last_heredoc_idx(file, redir_type) == i)
				unlink(exe_arg->tmp_name[exe_arg->child_num]);
		}
		else if ((redir_type[i] == OUTONE || redir_type[i] == OUTTWO)
			&& out_one_two(file[i], redir_type[i], fd, &out_count))
			return (1);
	}
	return (0);
}

static int	last_heredoc_idx(char **file, int *redir_type)
{
	int	i;
	int	idx;

	i = 0;
	idx = -1;
	while (file[i])
	{
		if (redir_type[i] == INTWO)
			idx = i;
		i++;
	}
	return (idx);
}

static int	in_two(t_execute_arg *exe_arg, int *fd, int *in_count)
{
	if (*in_count != 0)
		close(fd[0]);
	if (access(exe_arg->tmp_name[exe_arg->child_num], R_OK) == -1)
		return (print_perror(exe_arg->tmp_name[exe_arg->child_num]));
	fd[0] = open(exe_arg->tmp_name[exe_arg->child_num], O_RDONLY);
	if (fd[0] < 0)
		return (print_perror(exe_arg->tmp_name[exe_arg->child_num]));
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
