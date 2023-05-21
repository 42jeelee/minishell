/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:11:32 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 21:22:29 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

#define FAIL -1
#define CD_HOME 0
#define CD_OLD 1
#define CD_COMMON 2

static int	cd_set_flag(char **cmd, char **env);
static char	*get_path(char **cmd, char **env, int flag);
static int	change_pwds_in_env(char **env, char *after_pwd, char *after_oldpwd);

int	exe_cd(char **cmd, char **env)
{
	int		flag;
	char	*cd_path;
	char	*after_oldpwd;
	char	*after_pwd;

	flag = cd_set_flag(cmd, env);
	if (flag == FAIL)
		return (1);
	cd_path = get_path(cmd, env, flag);
	after_oldpwd = getcwd(0, 0);
	if (after_oldpwd == 0)
		return (1);
	if (chdir(cd_path) != 0)
		return (free_things(after_oldpwd, 0, 0, 0));
	after_pwd = getcwd(0, 0);
	if (after_pwd == 0)
		return (free_things(after_oldpwd, 0, 0, 0));
	if (flag == CD_OLD)
		printf("%s\n", after_pwd);
	if (change_pwds_in_env(env, after_pwd, after_oldpwd))
		return (free_things(after_oldpwd, after_pwd, 0, 0));
	return (0);
}

static int	change_pwds_in_env(char **env, char *after_pwd, char *after_oldpwd)
{
	int		pwd_idx;
	int		oldpwd_idx;
	char	*tmp;

	pwd_idx = find_str_idx_in_env("PWD", env);
	oldpwd_idx = find_str_idx_in_env("OLDPWD", env);
	if (pwd_idx != FAIL)
	{
		tmp = ft_strjoin("PWD=", after_pwd);
		if (tmp == 0)
			return (1);
		free(env[pwd_idx]);
		env[pwd_idx] = tmp;
	}
	if (oldpwd_idx != FAIL)
	{
		tmp = ft_strjoin("OLDPWD=", after_oldpwd);
		if (tmp == 0)
			return (1);
		free(env[oldpwd_idx]);
		env[oldpwd_idx] = tmp;
	}
	return (0);
}

static char	*get_path(char **cmd, char **env, int flag)
{
	if (flag == CD_HOME)
		return (&env[find_str_idx_in_env("HOME=", env)][5]);
	else if (flag == CD_OLD)
		return (&env[find_str_idx_in_env("OLDPWD=", env)][7]);
	else
		return (&cmd[1][0]);
}

static int	cd_set_flag(char **cmd, char **env)
{
	if (cmd[1] == 0)
	{
		if (find_str_idx_in_env("HOME=", env) == FAIL)
		{
			write(2, "cd: HOME not set\n", 17);
			return (FAIL);
		}
		return (CD_HOME);
	}
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
	{
		if (find_str_idx_in_env("OLDPWD=", env) == FAIL)
		{
			write(2, "cd: OLDPWD not set\n", 19);
			return (FAIL);
		}
		return (CD_OLD);
	}
	else
		return (CD_COMMON);
}
