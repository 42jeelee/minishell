/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:42:48 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/28 12:39:27 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static void	print_exit_error(char *word, char *msg);
static	int	is_numcmd(char *cmd);

int	exe_exit(char **cmd)
{
	if (cmd[1] == 0)
		exit(0);
	else if (is_numcmd(cmd[1]) == 0)
	{
		print_exit_error(cmd[1], "numeric argument required");
		exit(255);
	}
	else if (cmd[2] != 0)
		print_exit_error(0, "too many arguments");
	else
		exit(ft_atoi(cmd[1]));
	return (1);
}

static void	print_exit_error(char *word, char *msg)
{
	write(2, "exit: ", 6);
	if (word != 0)
	{
		write(2, word, ft_strlen(word));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static	int	is_numcmd(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

