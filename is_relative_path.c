/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_relative_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:45:38 by byejeon           #+#    #+#             */
/*   Updated: 2023/04/30 21:46:15 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

int	is_relative_path(char *cmd)
{
	size_t	i;
	size_t	cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd);
	if (cmd_len >= 2 && cmd[0] == '.' && cmd[1] == '/')
	{
		return (1);
	}
	else if (cmd_len >= 3 && cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
