/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:35 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/05 19:15:20 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds, char **env);
static int	init(t_arg *arg, t_execute_arg *exe_arg);
static void	free_exe_arg(t_execute_arg *exe_arg);

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
			i_hate_25_line(&exe_arg, arg, cmds, env);
			execve(exe_arg.cmd_path, cmds->cmd, env);
			exit(print_perror(cmds->cmd[0]));
		}
		cmds = cmds->next;
		exe_arg.i++;
	}
	close_pipes_exept(exe_arg.pfd, arg->num_of_cmd - 1, exe_arg.fd);
	while (exe_arg.i--)
		waitpid(exe_arg.pid[exe_arg.i], 0, 0);
	free_exe_arg(&exe_arg);
	return (0);
}

static void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds, char **env)
{
	pipe_redir(exe_arg->pfd, exe_arg->i, arg->num_of_cmd, exe_arg->fd);
	redir(cmds->file, cmds->redir_type, exe_arg->fd);
	if (arg->num_of_cmd > 1)
		close_pipes_exept(exe_arg->pfd, arg->num_of_cmd - 1, exe_arg->fd);
	if (cmds->builtin == 1)
		run_and_exit_builin();
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

void	print_env(char **env);
void	run_and_exit_builtin(t_cmds *cmds, char **env)
{
	if (ft_strcmp(cmds->cmd[0], "env"))
		print_env(env);
}

void	exe_echo(char **cmd)
{
	int	i;

	if (cmd[1])
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
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

static void	free_exe_arg(t_execute_arg *exe_arg)
{
	free(exe_arg->pid);
}
