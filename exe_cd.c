/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:11:32 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 16:29:31 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define FAIL -1
#define CD_HOME 0
#define CD_OLD 1
#define CD_COMMON 2

static int	cd_set_flag(char **cmd, char **env);
static int	str_idx_in_env(const char *str, char **env);
static char	*get_path(char **cmd, char **env, int flag);
static void	change_pwds_in_env(char **env, char *after_pwd, char *after_oldpwd);
//오류메세지에 파일 이름도 들어가면 좋겠는데 아님말고

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
		exit(print_perror("cd"));
	if (chdir(cd_path) != 0)
	{
		free(after_oldpwd);
		return (print_perror("cd"));
	}
	after_pwd = getcwd(0, 0);
	if (after_pwd == 0)
		exit(print_perror("cd"));
	if (flag == CD_OLD)
		printf("%s\n", after_pwd);
	change_pwds_in_env(env, after_pwd, after_oldpwd);
	return (0);
}

static void	change_pwds_in_env(char **env, char *after_pwd, char *after_oldpwd)
{
	int	pwd_idx;
	int	oldpwd_idx;

	pwd_idx = str_idx_in_env("PWD", env);
	oldpwd_idx = str_idx_in_env("OLDPWD", env);
	if (pwd_idx != FAIL)
	{
		free(env[pwd_idx]);
		env[pwd_idx] = ft_strjoin("PWD=", after_pwd);
		if (env[pwd_idx] == 0)
			exit(print_perror("cd"));
		free(after_pwd);
	}
	else
		free(after_pwd);
	if (oldpwd_idx != FAIL)
	{
		free(env[oldpwd_idx]);
		env[oldpwd_idx] = ft_strjoin("OLDPWD=", after_oldpwd);
		if (env[oldpwd_idx] == 0)
			exit(print_perror("cd"));
		free(after_oldpwd);
	}
	else
		free(after_oldpwd);
}

static char	*get_path(char **cmd, char **env, int flag)
{
	if (flag == CD_HOME)
		return (&env[str_idx_in_env("HOME=", env)][5]);
	else if (flag == CD_OLD)
		return (&env[str_idx_in_env("OLDPWD=", env)][7]);
	else
		return (&cmd[1][0]);
}

static int	cd_set_flag(char **cmd, char **env)
{
	if (cmd[1] == 0)
	{
		if (str_idx_in_env("HOME=", env) == FAIL)
		{
			write(2, "cd: HOME not set\n", 17);
			return (FAIL);
		}
		return (CD_HOME);
	}
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
	{
		if (str_idx_in_env("OLDPWD=", env) == FAIL)
		{
			write(2, "cd: OLDPWD not set\n", 19);
			return (FAIL);
		}
		return (CD_OLD);
	}
	else
		return (CD_COMMON);
}

static int	str_idx_in_env(const char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (FAIL);
}
