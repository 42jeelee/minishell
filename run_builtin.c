/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:58:21 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/05 21:01:59 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

void	print_env(char **env);
void	print_echo(char **cmd);
void	print_pwd(char **env);

int	run_builtin(t_cmds *cmds, char **env)
{
	if (ft_strncmp(cmds->cmd[0], "env", 4) == 0)
		print_env(env);
	else if (ft_strncmp(cmds->cmd[0], "echo", 5) == 0)
		print_echo(cmds->cmd);
	else if (ft_strncmp(cmds->cmd[0], "pwd", 4) == 0)
		print_pwd(env);
	else if (ft_strncmp(cmds->cmd[0], "exit", 5) == 0)
		exit(0);
	return 0;
}

void	print_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", env[i] + 4);
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
			printf("%s", cmd[i]);
			if (cmd[i + 1] != 0)
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1] != 0)
				printf(" ");
			i++;
		}
		printf("\n");
	}
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}
