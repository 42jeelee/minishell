/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_relative_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:45:38 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 14:25:34 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_relative_path(char *cmd)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] == '/')
		return (1);
	if (cmd_len >= 2 && cmd[0] == '.' && cmd[1] == '/')
		return (1);
	else if (cmd_len >= 3 && cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		return (1);
	return (0);
}
