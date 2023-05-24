/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/24 18:12:20 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static int	init(t_arg *arg, t_cmds *cmds, t_execute_arg *exe_arg);
static void	init_2(t_arg *arg, t_execute_arg *exe_arg);
static void	run_child_process(t_execute_arg *exe_arg, t_arg *arg,
				t_cmds *cmds, char ***env);

int	exe_cmd_line(t_arg *arg, t_cmds *cmds, char ***env)
{
	t_execute_arg	exe_arg;

	if (init(arg, cmds, &exe_arg))
		return (print_perror("error"));
	if (heredoc(cmds, &exe_arg) != 0)
		return (free_things(exe_arg.pid, exe_arg.pfd, 0, exe_arg.tmp_name));
	if (arg->num_of_cmd == 1 && cmds->builtin == 1)
	{
		if (redir(cmds->file, cmds->redir_type, exe_arg.fd, &exe_arg) != 0)
			return (1);
		return (run_builtin(cmds, env, &exe_arg));
	}
	while (cmds)
	{
		parents_sig_init();
		exe_arg.pid[exe_arg.child_num] = fork();
		if (exe_arg.pid[exe_arg.child_num] == 0)
			run_child_process(&exe_arg, arg, cmds, env);
		cmds = cmds->next;
		exe_arg.child_num++;
	}
	close_pipes_exept(exe_arg.pfd, arg->num_of_cmd - 1, exe_arg.fd);
	wait_childs(&exe_arg);
	close_and_free_things(&exe_arg);
	return (WEXITSTATUS(exe_arg.exit_code));
}

static void	run_child_process(t_execute_arg *exe_arg, t_arg *arg,
				t_cmds *cmds, char ***env)
{
	fork_sig_init(1);
	pipe_redir(exe_arg->pfd, exe_arg->child_num, arg->num_of_cmd, exe_arg->fd);
	if (redir(cmds->file, cmds->redir_type, exe_arg->fd, exe_arg) != 0)
		exit(1);
	if (arg->num_of_cmd > 1)
		close_pipes_exept(exe_arg->pfd, arg->num_of_cmd - 1, exe_arg->fd);
	if (cmds->builtin == 1)
		exit(run_builtin(cmds, env, exe_arg));
	if (is_relative_path(cmds->cmd[0]))
	{
		exe_arg->cmd_path = cmds->cmd[0];
		if (access(exe_arg->cmd_path, X_OK) == -1)
		{
			print_perror(exe_arg->cmd_path);
			exit(126);
		}
	}
	else
		cmd_abs_path(cmds->cmd[0], exe_arg->path, &exe_arg->cmd_path);
	execve(exe_arg->cmd_path, cmds->cmd, *env);
	exit(print_perror(cmds->cmd[0]));
}

static int	init(t_arg *arg, t_cmds *cmds, t_execute_arg *exe_arg)
{
	init_2(arg, exe_arg);
	exe_arg->pid = (pid_t *)malloc(sizeof(pid_t) * arg->num_of_cmd);
	if (exe_arg->pid == 0)
		return (1);
	if (arg->num_of_cmd == 1)
		exe_arg->pfd = 0;
	else if (arg->num_of_cmd > 1)
	{
		exe_arg->pfd = make_pipes(arg->num_of_cmd - 1);
		if (exe_arg->pfd == 0)
			return (free_things(exe_arg->pid, 0, 0, 0));
	}
	exe_arg->tmp_name = make_tmp_name(cmds);
	if (exe_arg->tmp_name == 0)
		return (free_things(exe_arg->pid, exe_arg->pfd, 0, 0));
	exe_arg->path = make_paths(arg->env);
	if (exe_arg->path == 0)
		return (free_things(exe_arg->pid, exe_arg->pfd, 0, exe_arg->tmp_name));
	return (0);
}

static void	init_2(t_arg *arg, t_execute_arg *exe_arg)
{
	exe_arg->i = 0;
	exe_arg->child_num = 0;
	exe_arg->exit_code = 0;
	exe_arg->fd[0] = -1;
	exe_arg->fd[1] = -1;
	exe_arg->restore_fd[0] = dup(0);
	exe_arg->restore_fd[1] = dup(1);
	exe_arg->arg = arg;
}
