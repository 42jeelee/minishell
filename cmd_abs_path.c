/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:38:25 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/06 18:56:32 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*print_error_message(char *cmd, char *message);
static char	*print_perror_massage(char *cmd);

char	*cmd_abs_path(char *cmd, char **paths)
{
	char	*out;
	int		i;

	i = -1;
	if (cmd[0] == '\0')
		return (print_error_message(cmd, ": command not found\n"));
	while (paths[++i])
	{
		out = ft_strjoin(paths[i], cmd);
		if (out == 0)
			exit(print_perror(cmd));
		if (access(out, F_OK) == 0)
		{
			if (access(out, X_OK) == 0)
				return (out);
			else
			{
				free(out);
				return (print_perror_massage(cmd));
			}
		}
		else
			free(out);
	}
	return (print_error_message(cmd, ": command not found\n"));
}

static char	*print_perror_massage(char *cmd)
{
	perror(cmd);
	return (0);
}

static char	*print_error_message(char *cmd, char *message)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	return (0);
}
