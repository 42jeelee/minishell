/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:16:22 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/25 19:02:49 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_empty_cmd(t_cmds *cmd)
{
	if (!cmd)
		return (1);
	return (!((cmd->cmd)[0] || (cmd->file)[0] || (cmd->redir_type)[0]));
}

char	*ft_stridxdup(char *str, int start, int end)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * (end - start));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < end - start)
		new[i] = (str + start)[i];
	new[i] = 0;
	return (new);
}
