/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/03 15:38:50 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds);
static int	init(t_arg *arg, t_execute_arg *exe_arg);

int		exe_cmd_line(t_arg *arg, t_cmds *cmds, char **env)
{
	t_execute_arg	exe_arg;

	if (init(arg, &exe_arg))
		return (print_perror("error"));
	while (cmds)
	{
		exe_arg.pid[exe_arg.i] = fork();
		if (exe_arg.pid[exe_arg.i] == 0)
		{
			i_hate_25_line(&exe_arg, arg, cmds);
			execve(exe_arg.cmd_path, cmds->cmd, env);
			exit(print_perror(cmds->cmd[0]));
		}
		cmds = cmds->next;
		exe_arg.i++;
	}
	close_pipes_exept(exe_arg.pfd, arg->num_of_cmd - 1, exe_arg.fd);
	while (exe_arg.i--)
		waitpid(exe_arg.pid[exe_arg.i], 0, 0);
	return (0);
}

static void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds)
{
	pipe_redir(exe_arg->pfd, exe_arg->i, arg->num_of_cmd, exe_arg->fd);
	redir(cmds->file, cmds->redir_type, exe_arg->fd);
	if (arg->num_of_cmd > 1)
		close_pipes_exept(exe_arg->pfd, arg->num_of_cmd - 1, exe_arg->fd);
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
}

static int	init(t_arg *arg, t_execute_arg *exe_arg)
{
	exe_arg->i = 0;
	exe_arg->fd[0] = -1;
	exe_arg->fd[1] = -1;
	exe_arg->pid = (pid_t *)malloc(sizeof(pid_t) * arg->num_of_cmd);
	if (exe_arg->pid == 0)
		return (1);
	if (arg->num_of_cmd)
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