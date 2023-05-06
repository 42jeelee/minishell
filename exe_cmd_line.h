/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:57 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/06 19:46:12 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMD_LINE_H
# define EXE_CMD_LINE_H

# include "common.h"

int		exe_cmd_line(t_arg *arg, t_cmds *cmds, char **env);
int		run_builtin(t_cmds *cmds, char **env, t_execute_arg *exe_arg);
char	*cmd_abs_path(char *cmd, char **paths);
int		**make_pipes(int num_of_pipe);
void	close_pipes_exept(int **pfd, int num_of_pipe, int *fd);
int		is_relative_path(char *cmd);

void	pipe_redir(int **pfd, int i, int num_of_cmd, int *fd);
void	redir(char **file, int *redir_type, int *fd);

#endif
