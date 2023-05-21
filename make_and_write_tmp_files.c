/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_and_write_tmp_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:21:00 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 16:30:28 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static void	open_write_close(t_cmds *cmds, t_execute_arg *exe_arg,
				int cmds_idx, int redir_idx);

// fd 에러시 수정 필요할듯
void	make_and_write_tmp_files(t_cmds *cmds, t_execute_arg *exe_arg)
{
	int		cmds_idx;
	int		redir_idx;

	cmds_idx = 0;
	while (cmds)
	{
		redir_idx = 0;
		while (cmds->redir_type[redir_idx])
		{
			if (cmds->redir_type[redir_idx] == INTWO)
			{
				if (access(exe_arg->tmp_name[cmds_idx], F_OK) == 0)
					unlink(exe_arg->tmp_name[cmds_idx]);
				open_write_close(cmds, exe_arg, cmds_idx, redir_idx);
			}
			redir_idx++;
		}
		cmds_idx++;
		cmds = cmds->next;
	}
}

static void	open_write_close(t_cmds *cmds, t_execute_arg *exe_arg,
				int cmds_idx, int redir_idx)
{
	int		fd;
	char	*str;

	fd = open(exe_arg->tmp_name[cmds_idx], O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		exit(print_perror("heredoctmpfile"));
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(cmds->file[redir_idx], str, ft_strlen(str) + 1) == 0)
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
}
