/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:11:32 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/07 19:15:04 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct cd_home_arg
{
	int		pwd_idx;
	int		oldpwd_idx;
	char	*home_path;
	char	*after_pwdenv;
	char	*after_oldpwdenv;
}	t_cd_arg;

int	is_in_env(char *str, char **env);
int	exe_cd_home(char **env);
int	exe_cd_oldpwd(char **env);
void	exe_cd(char **cmd, char **env)
{
	if (cmd[1] == 0)
		exe_cd_home(env);
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
		exe_cd_oldpwd(env);
	else

}

void	exe_cd_common(char *cmd, char **env)
{
	t_cd_arg	cd_arg;

	chdir(cmd[1]);

}

int	init_cd_common(t_cd_arg *cd_arg, char **cmd, char **env)
{
	cd_arg->pwd_idx = is_in_env("PWD=", env);
	cd_arg->oldpwd_idx = is_in_env("OLDPWD=", env);
	cd_arg->after_pwdenv = ft_strjoin("PWD=", );
	cd_arg->after_oldpwdenv =
}

int	init_cd_oldpwd(t_cd_arg *cd_arg, char **env);
int	exe_cd_oldpwd(char **env)
{
	t_cd_arg	cd_arg;

	if (init_cd_oldpwd(&cd_arg, env))
		return (1);
	chdir(env[cd_arg.oldpwd_idx] + 7);
	printf("%s\n", env[cd_arg.oldpwd_idx] + 7);
	env[cd_arg.pwd_idx] = cd_arg.after_pwdenv;
	env[cd_arg.oldpwd_idx] = cd_arg.after_oldpwdenv;
	return (0);
}

int	init_cd_oldpwd(t_cd_arg *cd_arg, char **env)
{
	char	*tmp;

	cd_arg->pwd_idx = is_in_env("PWD=", env);
	cd_arg->oldpwd_idx = is_in_env("OLDPWD=", env);
	if (cd_arg->oldpwd_idx == -1)
	{
		write(2, "cd: OLDPWD not set\n", 19);
		return (1);
	}
	if (cd_arg->pwd_idx != 1)
		cd_arg->after_pwdenv = ft_strjoin("PWD=", env[cd_arg->oldpwd_idx] + 7);
	tmp = getcwd(0, 0);
	if (tmp == 0 || cd_arg->after_pwdenv == 0)
		exit(12);
	if (cd_arg->oldpwd_idx != 1)
	{
		cd_arg->after_oldpwdenv = ft_strjoin("OLDPWD=", tmp);
		if (cd_arg->after_oldpwdenv == 0)
			exit (12);
	}
	free(tmp);
	return (0);
}

int	init_cd_home(t_cd_arg *cd_arg, char **env);
int	exe_cd_home(char **env)
{
	t_cd_arg	cd_arg;

	if (init_cd_home(&cd_arg, env) == 1)
		return (1);
	chdir(cd_arg.home_path);
	if (cd_arg.pwd_idx != -1)
		env[cd_arg.pwd_idx] = cd_arg.after_pwdenv;
	if (cd_arg.oldpwd_idx != -1)
		env[cd_arg.oldpwd_idx] = cd_arg.after_oldpwdenv;
	return (0);
}

int	init_cd_home(t_cd_arg *cd_arg, char **env)
{
	int		i;
	char	*tmp;

	i = is_in_env("HOME=", env);
	cd_arg->pwd_idx = is_in_env("PWD=", env);
	cd_arg->oldpwd_idx = is_in_env("OLDPWD=", env);
	if (i == -1)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	cd_arg->home_path = ft_strdup(env[i] + 5);
	cd_arg->after_pwdenv = ft_strjoin("PWD=", cd_arg->home_path);
	tmp = getcwd(0, 0);
	cd_arg->after_oldpwdenv = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	return (0);
}

int	is_in_env(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	free_things(void *a, void *b, void *c, void *d)
{
	if (a != 0)
		free(a);
	if (b != 0)
		free(b);
	if (c != 0)
		free(c);
	if (d != 0)
		free(d);
}
