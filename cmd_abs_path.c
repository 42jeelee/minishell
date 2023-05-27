/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:38:25 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/27 17:56:40 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_message(char *cmd, char *message, int errnum);
static int	print_perror_massage(char *cmd, int errnum);

int	cmd_abs_path(char *cmd, char **paths, char **cmd_path)
{
	int		i;

	i = -1;
	if (paths == 0 || cmd[0] == '\0')
		exit(print_error_message(cmd, ": command not found\n", 127));
	while (paths[++i])
	{
		*cmd_path = ft_strjoin(paths[i], cmd);
		if (*cmd_path == 0)
			exit(print_perror(cmd));
		if (access(*cmd_path, F_OK) == 0)
		{
			if (access(*cmd_path, X_OK) == 0)
				return (0);
			else
			{
				free(*cmd_path);
				exit(print_perror_massage(cmd, 126));
			}
		}
		else
			free(*cmd_path);
	}
	exit(print_error_message(cmd, ": command not found\n", 127));
}

static int	print_perror_massage(char *cmd, int errnum)
{
	perror(cmd);
	return (errnum);
}

static int	print_error_message(char *cmd, char *message, int errnum)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	return (errnum);
}
