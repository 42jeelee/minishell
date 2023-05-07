/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/06 19:29:45 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init(t_arg *arg, t_execute_arg *exe_arg);
static void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds,
				char **env);
static void	close_and_free_things(t_execute_arg *exe_arg);

int	exe_cmd_line(t_arg *arg, t_cmds *cmds, char **env)
{
	t_execute_arg	exe_arg;

	if (init(arg, &exe_arg))
		return (print_perror("error"));
	if (arg->num_of_cmd == 1 && cmds->builtin == 1)
	{
		redir(cmds->file, cmds->redir_type, exe_arg.fd);
		return (run_builtin(cmds, env, &exe_arg));
	}
	while (cmds)
	{
		exe_arg.pid[exe_arg.i] = fork();
		if (exe_arg.pid[exe_arg.i] == 0)
			i_hate_25_line(&exe_arg, arg, cmds, env);
		cmds = cmds->next;
		exe_arg.i++;
	}
	close_pipes_exept(exe_arg.pfd, arg->num_of_cmd - 1, exe_arg.fd);
	while (exe_arg.i--)
		waitpid(exe_arg.pid[exe_arg.i], &exe_arg.stat_loc, 0);
	close_and_free_things(&exe_arg);
	return (exe_arg.stat_loc);
}

static void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds,
				char **env)
{
	pipe_redir(exe_arg->pfd, exe_arg->i, arg->num_of_cmd, exe_arg->fd);
	redir(cmds->file, cmds->redir_type, exe_arg->fd);
	if (arg->num_of_cmd > 1)
		close_pipes_exept(exe_arg->pfd, arg->num_of_cmd - 1, exe_arg->fd);
	if (cmds->builtin == 1)
		exit(run_builtin(cmds, env, exe_arg));
	if (is_relative_path(cmds->cmd[0]))
	{
		exe_arg->cmd_path = cmds->cmd[0];
		if (access(exe_arg->cmd_path, X_OK) == -1)
			exit(print_perror(exe_arg->cmd_path));
	}
	else
		exe_arg->cmd_path = cmd_abs_path(cmds->cmd[0], arg->path);
	if (exe_arg->cmd_path == 0)
		exit(1);
	execve(exe_arg->cmd_path, cmds->cmd, env);
	exit(print_perror(cmds->cmd[0]));
}

static int	init(t_arg *arg, t_execute_arg *exe_arg)
{
	exe_arg->i = 0;
	exe_arg->fd[0] = -1;
	exe_arg->fd[1] = -1;
	exe_arg->restore_fd[0] = dup(0);
	exe_arg->restore_fd[1] = dup(1);
	exe_arg->pid = (pid_t *)malloc(sizeof(pid_t) * arg->num_of_cmd);
	if (exe_arg->pid == 0)
		return (1);
	if (arg->num_of_cmd == 1)
		exe_arg->pfd = 0;
	else
	{
		exe_arg->pfd = make_pipes(arg->num_of_cmd - 1);
		if (exe_arg->pfd == 0)
		{
			free(exe_arg->pid);
			return (1);
		}
	}
	return (0);
}

static void	close_and_free_things(t_execute_arg *exe_arg)
{
	close(exe_arg->restore_fd[0]);
	close(exe_arg->restore_fd[1]);
}
