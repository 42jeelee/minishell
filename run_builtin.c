/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:58:21 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/06 21:32:41 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

void	print_env(char **env);
void	print_echo(char **cmd);
void	print_pwd(char **env);
int		exe_cd(char **cmd, char **env);

int	run_builtin(t_cmds *cmds, char **env, t_execute_arg *exe_arg)
{
	if (ft_strncmp(cmds->cmd[0], "env", 4) == 0)
		print_env(env);
	else if (ft_strncmp(cmds->cmd[0], "echo", 5) == 0)
		print_echo(cmds->cmd);
	else if (ft_strncmp(cmds->cmd[0], "pwd", 4) == 0)
		print_pwd(env);
	else if (ft_strncmp(cmds->cmd[0], "exit", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmds->cmd[0], "cd", 5) == 0)
		exe_cd(cmds->cmd, env);
	dup2(exe_arg->restore_fd[0], 0);
	dup2(exe_arg->restore_fd[1], 1);
	close(exe_arg->restore_fd[0]);
	close(exe_arg->restore_fd[1]);
	return (0);
}

int	set_pwd(char **env, char *path);
int	set_oldpwd(char **env, char *path);
int	exe_cd_home(char **cmd, char **env);
int	exe_cd_oldpwd(char **cmd, char **env);

int	exe_cd(char **cmd, char **env)
{
	if (cmd[1] == 0)
		return (exe_cd_home(cmd, env));
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
		return (exe_cd_oldpwd(cmd, env));
	else
	{
		if (chdir(cmd[1]) == -1)
			return (print_perror("cd"));
		return (0);
	}
}
//cd에서 고쳐야할게 산더미.
int	exe_cd_oldpwd(char **cmd, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			printf("%s\n", env[i] + 7);
			chdir(env[i] + 7);
			tmp = ft_strdup(env[i] + 7);
			if (tmp == 0)
				return (1);
			set_pwd(env, env[i] + 7);
			set_oldpwd(env, tmp);
			free(tmp);
			return (0);
		}
		i++;
	}
	write(2, "cd: OLDPWD not set\n", 19);
	return (1);
}

int	exe_cd_home(char **cmd, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			chdir(env[i] + 5);
			tmp = ft_strdup(env[i] + 5);
			if (tmp == 0)
				return (1);
			set_pwd(env, env[i] + 5);
			set_oldpwd(env, tmp);
			free(tmp);
			return (0);
		}
		i++;
	}
	write(2, "cd: HOME not set\n", 17);
	return (1);
}

// char ***env로 받아서 주소 자체를 바꿔줘야할 수도 있음
// (PWD가 존재하지 않아서 새로 늘려줘야 하는 경우)
// free하기위해서 env를 시작부터 말록해야됨.
int	set_pwd(char **env, char *path)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			env[i] = ft_strjoin("PWD=", path);
			if (env[i] == 0)
				return (1);
			return (0);
		}
		i++;
	}
}
//얘도 마찬가지
int	set_oldpwd(char **env, char *path)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			env[i] = ft_strjoin("OLDPWD=", path);
			if (env[i] == 0)
				return (1);
			return (0);
		}
		i++;
	}
}

void	print_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			write(1, env[i] + 4, ft_strlen(env[i]) - 4);
			write(1, "\n", 1);
			return ;
		}
		i++;
	}
}

void	print_echo(char **cmd)
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

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}
