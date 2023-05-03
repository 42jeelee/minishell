/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:06 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/02 22:45:07 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(t_cmds *cmd)
{
	ft_memset(cmd, 0, sizeof(t_cmds));
	if (create_int_list(&(cmd->redir_type)) == -1)
		return (-1);
	if (create_word_list(&(cmd->file)) == -1)
		return (-1);
	if (create_word_list(&(cmd->cmd)))
		return (-1);
	cmd->next = 0;
	cmd->prev = 0;
	return (0);
}
