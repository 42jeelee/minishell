/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:57 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/28 11:51:16 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMD_LINE_H
# define EXE_CMD_LINE_H

# include "common.h"

int		exe_cmd_line(t_arg *arg, t_cmds *cmds, char ***env);

int		heredoc(t_cmds *cmds, t_execute_arg *exe_arg);
char	**make_tmp_name(t_cmds *cmds);
void	make_and_write_tmp_files(t_cmds *cmds, t_execute_arg *exe_arg);
char	**make_paths(char **env);

int		run_builtin(t_cmds *cmds, char ***env, t_execute_arg *exe_arg);
int		cmd_abs_path(char *cmd, char **paths, char **cmd_path);
int		**make_pipes(int num_of_pipe);
void	close_pipes_exept(int **pfd, int num_of_pipe, int *fd);
int		is_relative_path(char *cmd);

void	pipe_redir(int **pfd, int i, int num_of_cmd, int *fd);
int		redir(char **file, int *redir_type, int *fd, t_execute_arg *exe_arg);

int		exe_cd(char **cmd, char **env, t_execute_arg *exe_arg);

int		exe_export(char **cmd, char ***env);
int		exe_export_with_no_arg(char **env);

int		exe_unset(char **cmd, char **env);

int		free_things(void *a, void *b, void *c, char **d);

int		str_size_until_equal_or_null(const char *str);
int		find_str_idx_in_env(char *str, char **env);

void	wait_childs(t_execute_arg *exe_arg);
char	*ft_getpwd(char **env);
int		close_and_free_things(t_execute_arg *exe_arg);
int		exe_exit(char **cmd);

#endif
