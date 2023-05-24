/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:58:21 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/24 19:42:35 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static void	print_env(char **env);
static void	print_echo(char **cmd);
static int	print_pwd(t_execute_arg *exe_arg, char **env);
static int	run_builtin2(t_cmds *cmds, char ***env, t_execute_arg *exe_arg);

int	run_builtin(t_cmds *cmds, char ***env, t_execute_arg *exe_arg)
{
	if (ft_strncmp(cmds->cmd[0], "env", 4) == 0)
		print_env(*env);
	else if (ft_strncmp(cmds->cmd[0], "echo", 5) == 0)
		print_echo(cmds->cmd);
	else if (ft_strncmp(cmds->cmd[0], "pwd", 4) == 0)
		print_pwd(exe_arg, *env);
	else if (ft_strncmp(cmds->cmd[0], "exit", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmds->cmd[0], "cd", 3) == 0)
	{
		exe_arg->exit_code = exe_cd(cmds->cmd, *env, exe_arg);
		if (exe_arg->exit_code != 0)
			print_perror("cd");
	}
	run_builtin2(cmds, env, exe_arg);
	close_and_free_things(exe_arg);
	return (exe_arg->exit_code);
}

static int	run_builtin2(t_cmds *cmds, char ***env, t_execute_arg *exe_arg)
{
	if (ft_strncmp(cmds->cmd[0], "export", 7) == 0)
		exe_arg->exit_code = exe_export(cmds->cmd, env);
	else if (ft_strncmp(cmds->cmd[0], "unset", 6) == 0)
		exe_arg->exit_code = exe_unset(cmds->cmd, *env);
	dup2(exe_arg->restore_fd[0], 0);
	dup2(exe_arg->restore_fd[1], 1);
	close(exe_arg->restore_fd[0]);
	close(exe_arg->restore_fd[1]);
	return (0);
}

static int	print_pwd(t_execute_arg *exe_arg, char **env)
{
	char	*pwd;

	pwd = ft_getpwd(env);
	if (pwd == 0)
	{
		write(1, exe_arg->arg->pwd, ft_strlen(exe_arg->arg->pwd));
		write(1, "\n", 1);
	}
	else
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
	}
	return (0);
}

static void	print_echo(char **cmd)
{
	int	i;

	if (cmd[1] != 0 && ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		i = 2;
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1] != 0)
				write(1, " ", 1);
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1] != 0)
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
}

static void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
