/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:43:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/01 10:50:15 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_redir(int **pfd, int i, int num_of_cmd)
{
	if (i != 0)
		dup2(pfd[i - 1][0], 0);
	if (i != num_of_cmd - 1)
		dup2(pfd[i - 1][1], 1);
}

void	in_redir(t_cmds *cmds, int *fd)
{
	int		i;
	char	**infile;

	infile = cmds->infile;
	i = 0;
	while (infile[i])
	{
		if (i != 0)
			close(fd[0]);
		if (access(infile[i], R_OK) == -1)
			exit(print_perror(infile[i]));
		fd[0] = open(infile[i], O_RDONLY);
		if (fd[0] < 0)
			exit(print_perror(infile[i]));
		dup2(fd[0], 0);
		i++;
	}
}

void	out_redir(t_cmds *cmds, int *fd)
{
	int		i;
	char	**outfile;

	outfile = cmds->outfile;
	i = 0;
	while (outfile[i])
	{
		if (i != 0)
			close(fd[1]);
		if (access(outfile[i], F_OK) == 0)
			if (access(outfile[i], W_OK) != 0)
				exit(print_perror(outfile[i]));
		if (*cmds->out_redir_type == 1)
		{
			unlink(outfile[i]);
			fd[1] = open(outfile[i], O_WRONLY | O_CREAT, 0644);
		}
		else
			fd[1] = open(outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[1] < 0)
			exit(print_perror(outfile[i]));
		dup2(fd[1], 1);
		i++;
	}
}
