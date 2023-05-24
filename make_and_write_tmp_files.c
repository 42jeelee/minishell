/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_and_write_tmp_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:21:00 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/24 14:00:04 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_write_close(t_cmds *cmds, t_execute_arg *exe_arg,
				int cmds_idx, int redir_idx);

void	make_and_write_tmp_files(t_cmds *cmds, t_execute_arg *exe_arg)
{
	int				cmds_idx;
	int				redir_idx;

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
				exe_arg->exit_code = open_write_close(cmds, exe_arg,
						cmds_idx, redir_idx);
				if (exe_arg->exit_code > 0)
					return ;
			}
			redir_idx++;
		}
		cmds_idx++;
		cmds = cmds->next;
	}
}

static int	open_write_close(t_cmds *cmds, t_execute_arg *exe_arg,
				int cmds_idx, int redir_idx)
{
	int				fd;
	char			*str;
	char			*tmp;

	fd = open(exe_arg->tmp_name[cmds_idx], O_WRONLY | O_CREAT, 0644);
	tmp = cmds->file[redir_idx];
	if (fd < 0)
		return (1);
	while (1)
	{
		str = readline("> ");
		if (str == 0 && errno)
		{
			close(fd);
			return (1);
		}
		if (str == 0 || ft_strncmp(tmp, str, ft_strlen(str) + 1) == 0)
			break ;
		if (trim_word(&str, exe_arg->arg, 1))
		{
			free(str);
			return (1);
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
	return (0);
}
