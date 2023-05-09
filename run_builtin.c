/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:58:21 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/07 21:00:52 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

void	print_env(char **env);
void	print_echo(char **cmd);
void	print_pwd(void);
//cd 는 env에서 home을 읽어서 home으로 간다.
//cd - 는 env에서 OLDPWD를 읽어서 OLDPWD로 간다.
//cd ~ 는 ~ 로 간다.

int	run_builtin(t_cmds *cmds, char ***env, t_execute_arg *exe_arg)
{
	if (ft_strncmp(cmds->cmd[0], "env", 4) == 0)
		print_env(*env);
	else if (ft_strncmp(cmds->cmd[0], "echo", 5) == 0)
		print_echo(cmds->cmd);
	else if (ft_strncmp(cmds->cmd[0], "pwd", 4) == 0)
		print_pwd();
	else if (ft_strncmp(cmds->cmd[0], "exit", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmds->cmd[0], "cd", 5) == 0)
		exe_cd(cmds->cmd, *env);
	else if (ft_strncmp(cmds->cmd[0], "export", 7) == 0)
		exe_export(cmds->cmd, env);
	dup2(exe_arg->restore_fd[0], 0);
	dup2(exe_arg->restore_fd[1], 1);
	close(exe_arg->restore_fd[0]);
	close(exe_arg->restore_fd[1]);
	return (0);
}

void	print_pwd(void)
{
	char	*str;

	str = getcwd(0, 0);
	if (str == 0)
		exit(12);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(str);
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
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
